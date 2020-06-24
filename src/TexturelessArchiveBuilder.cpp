#include <bsapacker/TexturelessArchiveBuilder.h>

#include <bsapacker/ArchiveBuilderHelper.h>
#include <QDirIterator>
#include <QApplication>
#include <QDebug>

namespace BsaPacker
{
	TexturelessArchiveBuilder::TexturelessArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir)
		: m_ArchiveBuilderHelper(archiveBuilderHelper), m_RootDirectory(rootDir)
	{
		this->m_Cancelled = false;
		this->m_Archive = std::make_unique<BSArchiveAuto>(this->m_RootDirectory.path());
	}

	uint32_t TexturelessArchiveBuilder::setFiles()
	{
		uint32_t incompressibleFiles = 0;
		uint32_t compressibleFiles = 0;
		int count = 0;
		const auto& dirString = (this->m_RootDirectory.path() + '/').toStdWString();
		const auto& rootDirFiles = this->m_ArchiveBuilderHelper->getRootDirectoryFilenames(dirString);
		qDebug() << "root is: " << m_RootDirectory.path() + '/';

		QDirIterator iterator(this->m_RootDirectory, QDirIterator::Subdirectories);
		while (iterator.hasNext()) {
			QApplication::processEvents();

			if (this->m_Cancelled) {
				this->m_Archive.reset();
				return 0;
			}

			const QString& filepath = iterator.next();
			const bool ignored = this->m_ArchiveBuilderHelper->isFileIgnorable(filepath, rootDirFilenames);

			Q_EMIT this->valueChanged(++count);
			if (ignored || filepath.endsWith(".dds", Qt::CaseInsensitive)) {
				continue;
			}

			this->m_ArchiveBuilderHelper->isIncompressible(filepath.toStdWString()) ? ++incompressibleFiles : ++compressibleFiles;
			auto fileBlob = disk_blob(
				 dirString,
				 filepath.toStdWString());
			this->m_Archive->add_file_from_disk(fileBlob);
			qDebug() << "file is: " << filepath;
		}
		this->m_Archive->setCompressed(!static_cast<bool>(incompressibleFiles));
		return incompressibleFiles + compressibleFiles;
	}

	void TexturelessArchiveBuilder::setShareData(const bool value)
	{
		this->m_Archive->setShareData(value);
	}

	std::unique_ptr<BSArchiveAuto> TexturelessArchiveBuilder::getArchive()
	{
		return std::move(this->m_Archive);
	}

	uint32_t TexturelessArchiveBuilder::getFileCount() const
	{
		return this->m_ArchiveBuilderHelper->getFileCount(this->m_RootDirectory);
	}

	QString TexturelessArchiveBuilder::getRootPath() const
	{
		return this->m_RootDirectory.path();
	}

	void TexturelessArchiveBuilder::cancel()
	{
		this->m_Cancelled = true;
	}
} // namespace BsaPacker
