#include <bsapacker/ArchiveBuilderHelper.h>

#include <QDirIterator>
#include <QtConcurrent/QtConcurrentMap>

#include "SettingsService.h"

#include <QDebug>

using std::filesystem::is_directory;
using std::filesystem::path;
using std::filesystem::directory_entry;
using std::filesystem::directory_iterator;
using std::filesystem::recursive_directory_iterator;

namespace BsaPacker
{
	const std::set<std::string> ArchiveBuilderHelper::INCOMPRESSIBLE_TYPES = { ".wav", ".ogg", ".mp3" };

	ArchiveBuilderHelper::ArchiveBuilderHelper(const ISettingsService* settingsService)
		: m_SettingsService(settingsService)
	{
	}
	uint32_t ArchiveBuilderHelper::getFileCount(const QDir& rootDirectory) const
	{
		QDirIterator it(rootDirectory, QDirIterator::Subdirectories);
		uint32_t count = 0;
		while (it.hasNext()) {
			it.next();
			count++;
		}
		return count;
	}

	QStringList ArchiveBuilderHelper::getRootDirectoryFilenames(const QDir& rootDirectory) const
	{
		const std::function<QString(const QFileInfo&)> getFilename = [](const QFileInfo& fi) {
			return fi.fileName();
		};
		return QtConcurrent::blockingMapped(rootDirectory.entryInfoList(QDir::Files),
											getFilename);
	}

	bool ArchiveBuilderHelper::isFileIgnorable(const QString& filepath, const QStringList& rootDirFilenames) const
	{
		return this->doesPathContainFiles(filepath, rootDirFilenames) || // ignore files within mod directory
			is_directory(filepath) || // ignore directories
			this->isExtensionBlacklisted(filepath); // ignore user blacklisted file types
	}

	bool ArchiveBuilderHelper::isIncompressible(const QString& filename) const
	{
		const auto& extension = filename.extension().string();
		const auto& count = ArchiveBuilderHelper::INCOMPRESSIBLE_TYPES.count(extension);
		const auto& result = count > 0;
		return result;
	}

	bool ArchiveBuilderHelper::isExtensionBlacklisted(const path& filepath) const
	{
		const auto& setting = this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_BLACKLISTED_FILES).toString().toStdString();
		std::set<std::string> blacklist;
		boost::split(blacklist, setting, [](char c){return c == ';';});

		const auto& extension = filepath.extension().string();
		const auto& count = blacklist.count(extension);
		const auto& result = count > 0;
		return result;
	}
} // namespace BsaPacker
