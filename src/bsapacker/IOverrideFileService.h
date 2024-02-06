#ifndef IOVERRIDEFILESERVICE_H
#define IOVERRIDEFILESERVICE_H

#include <QString>

namespace BsaPacker
{
	class IOverrideFileService
	{
	public:
		virtual ~IOverrideFileService() = default;
		virtual bool CreateOverrideFile(const int nexusId, const QString& archiveName) const = 0;
	};
}

#endif // IOVERRIDEFILESERVICE_H
