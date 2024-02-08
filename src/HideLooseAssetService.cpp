#include "HideLooseAssetService.h"

#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
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

		// Only hide loose files that were not excluded when creating the archive (blacklisted), so might still be needed by the mod
		QStringList blacklistExtensions = this->m_SettingsService->GetPluginSetting(SettingsService::SETTING_BLACKLISTED_FILES).toString().split(';');
		for (auto& ext : blacklistExtensions) {
			ext.prepend("*");
		}

		// Hide subdirectories
		const QString& absModDir = modDirectory.absolutePath();
		for (const QString& subDir : modDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
			const QString& absPath = absModDir + '/' + subDir;
			QDir dir(absPath);
			if (dir.dirName().endsWith(s_HiddenExt) || dir.isEmpty()) {
				continue;
			}
			if (!dir.rename(absPath, absPath + s_HiddenExt)) {
				qWarning() << "Failed to hide directory " << absPath;
			}
		}

		// Restore files with blacklisted extension to their original directories
		QDir renamerDir(absModDir);
		QDirIterator iterator(absModDir, blacklistExtensions, QDir::Files, QDirIterator::Subdirectories);
		while (iterator.hasNext()) {
			const QFileInfo& fileInfo(iterator.nextFileInfo());
			if (!renamerDir.mkpath(fileInfo.absolutePath().replace(s_HiddenExt, ""))) {
				qWarning() << "Failed to make directory " << fileInfo.absolutePath().replace(s_HiddenExt, "");
				continue;
			}
			renamerDir.rename(fileInfo.absoluteFilePath(), fileInfo.absoluteFilePath().replace(s_HiddenExt, ""));
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
