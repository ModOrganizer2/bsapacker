#ifndef IARCHIVEAUTOSERVICE_H
#define IARCHIVEAUTOSERVICE_H

#include <qlibbsarch/BSArchiveAuto.h>
#include <bsapacker/IModDto.h>

namespace BsaPacker
{
	class IArchiveAutoService
	{
	public:
		virtual ~IArchiveAutoService() = default;
		virtual void CreateBSA(BSArchiveAuto*, const QString&, bsa_archive_type_e) const = 0;
	};
}

#endif // IARCHIVEAUTOSERVICE_H
