#ifndef ARCHIVENAMESERVICE_H
#define ARCHIVENAMESERVICE_H

#include <bsapacker/IArchiveNameService.h>
#include <bsapacker/IModContext.h>

namespace BsaPacker
{
	class ArchiveNameService : public IArchiveNameService
	{
	public:
		ArchiveNameService(const IModContext* modContext);
		~ArchiveNameService() override = default;
		QString GetArchiveFullPath(bsa_archive_type_e type, const IModDto* modDto) const override;
		QString GetFileExtension() const override;
	private:
		const IModContext* m_ModContext = nullptr;

		QString Infix(bsa_archive_type_e type) const;
	};
}

#endif // ARCHIVENAMESERVICE_H
