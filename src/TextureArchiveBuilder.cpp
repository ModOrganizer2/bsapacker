#include <bsapacker/TextureArchiveBuilder.h>

#include <bsapacker/ArchiveBuilderHelper.h>
#include <QDirIterator>
#include <QApplication>
#include <QDebug>
#include "DirectXTex.h"

using namespace libbsarch;

namespace BsaPacker
{
	// 4 GiB limit for loading an archive in the Creation Kit. Game itself should have no limit
	const qint64 MAXSIZE = 4294967296;

	TextureArchiveBuilder::TextureArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir, const bsa_archive_type_t& type)
		: m_ArchiveBuilderHelper(archiveBuilderHelper), m_RootDirectory(rootDir), m_CurrentType(type)
	{
		this->m_Cancelled = false;
		this->m_Archives.push_back(std::make_unique<libbsarch::bs_archive_auto>(m_CurrentType));
		this->m_ArchiveIndex = 0;
	}

	uint32_t TextureArchiveBuilder::setFiles()
	{
		uint32_t incompressibleFiles = 0;
		uint32_t compressibleFiles = 0;
		int count = 0;
		qint64 totalSize = 0;
		const auto& dirString = (this->m_RootDirectory.path() + '/').toStdWString();
		const auto& rootDirFiles = this->m_ArchiveBuilderHelper->getRootDirectoryFilenames(dirString);
		qDebug() << "root is: " << m_RootDirectory.path() + '/';

		QDirIterator iterator(this->m_RootDirectory, QDirIterator::Subdirectories);
		while (iterator.hasNext()) {
			QApplication::processEvents();

			if (this->m_Cancelled) {
				for (auto& archive : m_Archives) {
					archive.reset();
				}
				return 0;
			}

			const QFileInfo& fileInfo = iterator.nextFileInfo();
			const bool ignored = this->m_ArchiveBuilderHelper->isFileIgnorable(fileInfo.absoluteFilePath().toStdWString(), rootDirFiles);

			Q_EMIT this->valueChanged(++count);
			if (ignored || !fileInfo.absoluteFilePath().endsWith(".dds", Qt::CaseInsensitive)) {
				continue;
			}

			if (this->m_ArchiveBuilderHelper->shouldSplitArchives()) {
				if (totalSize + fileInfo.size() > MAXSIZE) {
					this->m_Archives[m_ArchiveIndex]->set_compressed(!static_cast<bool>(incompressibleFiles));
					this->m_Archives[m_ArchiveIndex]->set_dds_callback(TextureArchiveBuilder::DDSCallback, this->getRootPath().toStdWString());
					incompressibleFiles = 0;
					compressibleFiles = 0;
					totalSize = 0;
					this->m_Archives.push_back(std::make_unique<libbsarch::bs_archive_auto>(m_CurrentType));
					++m_ArchiveIndex;
					this->setShareData(true);
				}
				totalSize += fileInfo.size();
			}

			this->m_ArchiveBuilderHelper->isIncompressible(fileInfo.absoluteFilePath().toStdWString()) ? ++incompressibleFiles : ++compressibleFiles;
			auto fileBlob = disk_blob(
				 dirString,
				fileInfo.absoluteFilePath().toStdWString());
			this->m_Archives[m_ArchiveIndex]->add_file_from_disk(fileBlob);
			qDebug() << "file is: " << fileInfo.absoluteFilePath();
		}
		this->m_Archives[m_ArchiveIndex]->set_compressed(!static_cast<bool>(incompressibleFiles));
		this->m_Archives[m_ArchiveIndex]->set_dds_callback(TextureArchiveBuilder::DDSCallback, this->getRootPath().toStdWString());
		return incompressibleFiles + compressibleFiles;
	}

	void TextureArchiveBuilder::setShareData(const bool value)
	{
		this->m_Archives[m_ArchiveIndex]->set_share_data(value);
	}

	std::vector<std::unique_ptr<libbsarch::bs_archive_auto>> TextureArchiveBuilder::getArchives()
	{
		return std::move(this->m_Archives);
	}

	uint32_t TextureArchiveBuilder::getFileCount() const
	{
		return this->m_ArchiveBuilderHelper->getFileCount(this->m_RootDirectory.path().toStdWString());
	}

	QString TextureArchiveBuilder::getRootPath() const
	{
		return this->m_RootDirectory.path();
	}

	void TextureArchiveBuilder::cancel()
	{
		this->m_Cancelled = true;
	}

	void TextureArchiveBuilder::DDSCallback(bsa_archive_t archive, const wchar_t* file_path, bsa_dds_info_t* dds_info, void* context)
	{
		const auto& path = *static_cast<std::wstring*>(context) + L'/' + std::wstring(file_path);

		auto image = std::make_unique<DirectX::ScratchImage>();
		DirectX::TexMetadata info;

		const auto hr = LoadFromDDSFile(path.c_str(), DirectX::DDS_FLAGS_NONE, &info, *image);

		if (FAILED(hr))
			throw std::runtime_error("Failed to open DDS");

		dds_info->width = static_cast<uint32_t>(info.width);
		dds_info->height = static_cast<uint32_t>(info.height);
		dds_info->mipmaps = static_cast<uint32_t>(info.mipLevels);
	}
} // namespace BsaPacker
