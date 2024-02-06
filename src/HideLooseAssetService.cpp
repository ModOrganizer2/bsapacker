#include "HideLooseAssetService.h"

#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QtConcurrent/QtConcurrentMap>

#include "SettingsService.h"

namespace BsaPacker
{
	QString HideLooseAssetService::s_HiddenExt(".mohidden");

	HideLooseAssetService::HideLooseAssetService(const ISettingsService* settingsService)
		: m_SettingsService(settingsService)
	{
	}

	bool HideLooseAssetService::HideLooseAssets(const QDir& modDirectory) const
	{
		if (!this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_HIDE_LOOSE_ASSETS).toBool()) {
			return false;
		}

		// Get QStringList of blacklisted extensions and remove the . so we can match with QFileInfo::suffix later
		// This relies on the extension being in format .ext
		QStringList blacklistExtensions = this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_BLACKLISTED_FILES).toString().split(';');
		for (auto& ext : blacklistExtensions) {
			ext.remove(0, 1);
		}

		// loop through subdirectories in mod directory
		const QString& absModDir = modDirectory.absolutePath();
		for (const QString& subDir : modDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
			const QString& absPath = absModDir + '/' + subDir;
			QDir dir(absPath);
			
			// directory is already hidden or empty so skip it
			if (dir.dirName().endsWith(s_HiddenExt) || dir.isEmpty()) {
				continue;
			}

			// get QStringList of file paths that should not be hidden and count total files
			int fileCount = 0;
			QStringList blacklistFilePaths;
			QDirIterator iterator(absPath, QDir::Files, QDirIterator::Subdirectories);
			while (iterator.hasNext()) {
				QFileInfo fileInfo(iterator.nextFileInfo());
				if (blacklistExtensions.contains(fileInfo.suffix(), Qt::CaseInsensitive)) {
					blacklistFilePaths.append(fileInfo.absoluteFilePath());
				}
				++fileCount;
			}

			// directory has only blacklisted files so do nothing
			if (fileCount == blacklistFilePaths.count())
				continue;

			// directory has no blacklisted files so hide it
			if (blacklistFilePaths.isEmpty()) {
				if (!dir.rename(absPath, absPath + s_HiddenExt)) {
					qWarning() << "Failed to rename " << absPath << " to " << absPath + s_HiddenExt;
				}
				continue;
			}

			// directory has some blacklisted files so hide the directory then move blacklisted files out of it
			if (!dir.rename(absPath, absPath + s_HiddenExt)) {
				qWarning() << "Failed to rename " << absPath << " to " << absPath + s_HiddenExt;
				continue;
			}

			const qsizetype absPathLength = absPath.length();
			for (const auto& blacklistedPath : blacklistFilePaths) {
				QFileInfo fileInfo(blacklistedPath);
				QDir fileDir(fileInfo.absolutePath());

				if (!fileDir.exists() && !fileDir.mkpath(fileDir.absolutePath())) {
					qWarning() << "Failed to create path " << fileDir.absolutePath();
					continue;
				}

				QString hiddenPath(blacklistedPath);
				hiddenPath.insert(absPathLength, s_HiddenExt);
				if (!fileDir.rename(hiddenPath, blacklistedPath)) {
					qWarning() << "Failed to rename " << hiddenPath << " to " << blacklistedPath;
				}
			}
		}
		return true;

		/*
		const std::function<void(const QString&)> hideFolder = [&](const QString& subDir)
		{
			const QString& absPath = absModDir + '/' + subDir;
			QDir dir(absPath);
			if (!dir.dirName().endsWith(".mohidden"))
				dir.rename(absPath, absPath + ".mohidden");
		};
		*/
		//QtConcurrent::blockingMap(modDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot), hideFolder);
	}
}
