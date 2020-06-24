#include <bsapacker/ArchiveBuilderHelper.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>

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
	uint32_t ArchiveBuilderHelper::getFileCount(const path& rootDirectory) const
	{
		uint32_t count = 0;
		for(auto& p : recursive_directory_iterator(rootDirectory)) {
			count++;
		}
		return count;
	}

	std::vector<path::string_type> ArchiveBuilderHelper::getRootDirectoryFilenames(const path& rootDirectory) const
	{
		std::vector<path::string_type> filenames;
		for (const auto& entry : directory_iterator(rootDirectory)) {
			filenames.push_back(entry.path().filename().native());
		}
		return filenames;
	}

	bool ArchiveBuilderHelper::isFileIgnorable(const path& filepath, const std::vector<path::string_type>& rootDirFilenames) const
	{
		return this->doesPathContainFiles(filepath, rootDirFilenames) || // ignore files within mod directory
			is_directory(filepath) || // ignore directories
			this->isExtensionBlacklisted(filepath); // ignore user blacklisted file types
	}

	bool ArchiveBuilderHelper::isIncompressible(const path& filename) const
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

	bool ArchiveBuilderHelper::doesPathContainFiles(const path& filepath, const std::vector<path::string_type>& files) const
	{
		return std::find(files.begin(), files.end(), filepath.filename()) != files.end();
	}
} // namespace BsaPacker
