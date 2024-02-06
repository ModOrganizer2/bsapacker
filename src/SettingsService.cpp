#include "SettingsService.h"

namespace BsaPacker
{
	const QString& SettingsService::SETTING_HIDE_LOOSE_ASSETS = QStringLiteral("hide_loose_assets");
	const QString& SettingsService::SETTING_CREATE_PLUGINS = QStringLiteral("create_plugins");
	const QString& SettingsService::SETTING_CREATE_OVERRIDES = QStringLiteral("create_overrides");
	const QString& SettingsService::SETTING_BLACKLISTED_FILES = QStringLiteral("blacklisted_files");
	//const QString& SettingsService::SETTING_SPLIT_ARCHIVES = "split_archives";

	const QList<MOBase::PluginSetting>& SettingsService::PluginSettings = {
		MOBase::PluginSetting(SettingsService::SETTING_HIDE_LOOSE_ASSETS, QObject::tr("After creating the archive, set loose assets to hidden."), false),
		MOBase::PluginSetting(SettingsService::SETTING_CREATE_PLUGINS, QObject::tr("Create a dummy plugin to load the archive if one does not exist."), false),
		MOBase::PluginSetting(SettingsService::SETTING_CREATE_OVERRIDES, QObject::tr("Create an .override file to allow overwriting vanilla archive files. This only works for Fallout 3 and New Vegas and requires Command Extender or JIP LN NVSE respectively."), false),
		MOBase::PluginSetting(SettingsService::SETTING_BLACKLISTED_FILES, QObject::tr("Specify a semi-colon seperated list of file extensions to ignore when packing."), ".txt;.hkx;.xml;.ini;.bk2")
		//MOBase::PluginSetting(SettingsService::SETTING_SPLIT_ARCHIVES, QObject::tr("Automatically create multiple archives if they exceed the size limit."), false);
	};

	SettingsService::SettingsService(MOBase::IOrganizer* organizer)
		: m_Organizer(organizer)
	{
	}

	QVariant SettingsService::GetPluginSetting(const QString& setting) const
	{
		return this->m_Organizer->pluginSetting(QStringLiteral("BSA Packer"), setting);
	}
} // namespace BsaPacker
