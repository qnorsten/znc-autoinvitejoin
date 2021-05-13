#include <znc/main.h>
#include <znc/Modules.h>
#include <znc/Chan.h>
#include <znc/IRCNetwork.h>

/*
 * AutoInviteJoin module
 * Author: Cizzle
 * Description: Joins saved channels upon invite, even when the user is not connected.
 * Version: 20160621
 */

using std::set;

class CAutoInviteJoin : public CModule {
public:

	MODCONSTRUCTOR(CAutoInviteJoin) {}

	virtual ~CAutoInviteJoin() {}

	virtual EModRet OnInvite(const CNick& Nick, const CString& sChan) override {
		CIRCNetwork *pNetwork = GetNetwork();
		if (pNetwork) {
				
			// /* Only autojoin channels in our config */
			// CChan *invChan = pNetwork->FindChan(sChan);
			// if (invChan) {
				// set<CChan*> sChans;
				// sChans.insert(invChan);
				// pNetwork->JoinChans(sChans);
			// }
			
			CChan *invChan = pNetwork->FindChan(sChan);
			
			/* Add Channel if it do not exist already */
			/* TODO add config option for this */
			if (!invChan) {
				bool addChan = pNetwork->AddChan(sChan, false);
				if (addChan) {
					CChan *invChan = pNetwork->FindChan(sChan);
				}
				
			}
			
			if (invChan) {
				set<CChan*> sChans;
				sChans.insert(invChan);
				pNetwork->JoinChans(sChans);
			}
		}

		return CONTINUE;
	}
};

template <>
void TModInfo<CAutoInviteJoin>(CModInfo& Info) {
	Info.SetWikiPage("autoinvitejoin");
	Info.AddType(CModInfo::UserModule);
	Info.AddType(CModInfo::GlobalModule);
}

NETWORKMODULEDEFS(CAutoInviteJoin, "Auto joins saved channels on invite even when the user is not connected.")
