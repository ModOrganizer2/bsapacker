#ifndef ARCHIVEBUILDERHELPER_H
#define ARCHIVEBUILDERHELPER_H

#include <bsapacker/IArchiveBuilderHelper.h>
#include <bsapacker/ISettingsService.h>
#include <set>
#include <string>

namespace BsaPacker
{
	class ArchiveBuilderHelper : public IArchiveBuilderHelper
	{
	public:
		ArchiveBuilderHelper(const ISettingsService* settingsService);
		~ArchiveBuilderHelper() override = default;
		ArchiveBuilderHelper(const ArchiveBuilderHelper&) = delete;
		ArchiveBuilderHelper& operator=(const ArchiveBuilderHelper&) = delete;
		ArchiveBuilderHelper(ArchiveBuilderHelper&&) = delete;
		ArchiveBuilderHelper& operator=(ArchiveBuilderHelper&&) = delete;

		[[nodiscard]] bool isFileIgnorable(const QString&, const QStringList&) const override;
		[[nodiscard]] bool isIncompressible(const QString&) const override;
		[[nodiscard]] bool isExtensionBlacklisted(const QString&) const override;
		[[nodiscard]] uint32_t getFileCount(const QDir&) const override;
		[[nodiscard]] QStringList getRootDirectoryFilenames(const QDir&) const override;

		const static std::array <QString, 3> INCOMPRESSIBLE_TYPES;

	private:
		const static std::set<std::string> INCOMPRESSIBLE_TYPES;
		const ISettingsService* m_SettingsService = nullptr;
	};
} // namespace BsaPacker

#endif // ARCHIVEBUILDERHELPER_H
