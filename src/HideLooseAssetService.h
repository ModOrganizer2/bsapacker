#ifndef HIDELOOSEASSETSERVICE_H
#define HIDELOOSEASSETSERVICE_H

#include <bsapacker/IHideLooseAssetService.h>
#include <bsapacker/ISettingsService.h>

namespace BsaPacker
{
	class HideLooseAssetService : public IHideLooseAssetService
	{
	public:
		HideLooseAssetService() = default;
		HideLooseAssetService(const ISettingsService* settingsService);
		~HideLooseAssetService() override = default;
		bool HideLooseAssets(const QDir& modDirectory) const override;

	private:
		const ISettingsService* m_SettingsService = nullptr;
	};
}

#endif // HIDELOOSEASSETSERVICE_H
