#include <bsapacker/GeneralArchiveBuilder.h>

#include <bsapacker/ArchiveBuilderHelper.h>
#include <QDirIterator>
#include <QApplication>
#include <QDebug>

using namespace libbsarch;

namespace BsaPacker
{
	GeneralArchiveBuilder::GeneralArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir)
		: m_ArchiveBuilderHelper(archiveBuilderHelper), m_RootDirectory(rootDir)
	{
		this->m_Cancelled = false;
		this->m_Archive = std::make_unique<BSArchiveAuto>(this->m_RootDirectory.path());
	}

	uint32_t GeneralArchiveBuilder::setFiles()
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
			const bool ignored = this->m_ArchiveBuilderHelper->isFileIgnorable(filepath, rootDirFiles);

			Q_EMIT this->valueChanged(++count);
			if (ignored) {
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

	void GeneralArchiveBuilder::setShareData(const bool value)
	{
		this->m_Archive->setShareData(value);
	}

	std::unique_ptr<BSArchiveAuto> GeneralArchiveBuilder::getArchive()
	{
		return std::move(this->m_Archive);
	}

	uint32_t GeneralArchiveBuilder::getFileCount() const
	{
		return this->m_ArchiveBuilderHelper->getFileCount(this->m_RootDirectory);
	}

	QString GeneralArchiveBuilder::getRootPath() const
	{
		return this->m_RootDirectory.path();
	}

	void GeneralArchiveBuilder::cancel()
	{
		this->m_Cancelled = true;
	}
} // namespace BsaPacker
