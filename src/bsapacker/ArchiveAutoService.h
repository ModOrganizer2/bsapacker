#ifndef ARCHIVEAUTOSERVICE_H
#define ARCHIVEAUTOSERVICE_H

#include <bsapacker/IModDto.h>
#include <bsapacker/IArchiveAutoService.h>
#include <qlibbsarch/BSArchiveAuto.h>

namespace BsaPacker
{
	class ArchiveAutoService : public IArchiveAutoService
	{
	public:
		ArchiveAutoService() = default;
		~ArchiveAutoService() override = default;
		ArchiveAutoService(const ArchiveAutoService&) = delete;
		ArchiveAutoService& operator=(const ArchiveAutoService&) = delete;
		ArchiveAutoService(ArchiveAutoService&&) = default;
		ArchiveAutoService& operator=(ArchiveAutoService&&) = default;

		void CreateBSA(BSArchiveAuto* archive, const QString& archiveName, bsa_archive_type_e type) const override;
	};
} // namespace BsaPacker

#endif // ARCHIVEAUTOSERVICE_H
