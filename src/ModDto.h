#ifndef MODMETADTO_H
#define MODMETADTO_H

#include <bsapacker/IModDto.h>

#include <QDir>
#include <QString>

namespace BsaPacker
{
	class ModDto : public IModDto
	{
	public:
		ModDto(const int nexusId, const QString& modDir, const QString& archiveName, const QString& archiveExtension);
		~ModDto() override = default;
		[[nodiscard]] QString ArchiveExtension() const override;
		[[nodiscard]] QString ArchiveName() const override;
		[[nodiscard]] QString Directory() const override;
		[[nodiscard]] QString ModForename() const override;
		[[nodiscard]] int NexusId() const override;

	private:
		const int m_NexusId;
		const QDir m_Path;
		const QString m_ArchiveName;
		const QString m_ArchiveExtension;
	};
} // namespace BsaPacker

#endif // MODMETADTO_H
