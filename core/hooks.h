#ifndef HOOKS_H
#define HOOKS_H

#include "../sdk/framework/utils/vfhook.h"
#include "../sdk/framework/utils/atomic_lock.h"
#include "../sdk/source_csgo/sdk.h"
#include "../sdk/source_shared/hooks.h"
#include <unordered_map>

#define GetOriginal1(NAME) GetOriginal<decltype(NAME)*>((void*)NAME);
#define GetOriginal2(TYPE, NAME) GetOriginal<TYPE>((void*)NAME);

#define ID2(x) x
#define GET_MACRO2(_1,_2, NAME,...) NAME
#define GetOriginal(...) ID2(GET_MACRO2(__VA_ARGS__, GetOriginal2, GetOriginal1)(__VA_ARGS__))

extern VFuncHook* hookClientMode;
extern VFuncHook* hookPanel;
extern VFuncHook* hookViewRender;
extern VFuncHook* hookSurface;

namespace CSGOHooks
{
#ifdef PT_VISUALS
	void __stdcall PaintTraverse(STDARGS PC vgui::VPANEL vpanel, bool forceRepaint, bool allowForce);
#endif

	extern AtomicLock hookLock;
	extern std::unordered_map<C_BasePlayer*, VFuncHook*> entityHooks;
	void __fastcall EntityDestruct(FASTARGS);
	bool __fastcall SetupBones(FASTARGS, matrix3x4_t*, int, int, float);
	void __fastcall OnRenderStart(FASTARGS);
	void __fastcall OverrideView(FASTARGS, CViewSetup*);
	int __fastcall DoPostScreenSpaceEffects(FASTARGS, CViewSetup*);
	void __fastcall LockCursor(FASTARGS);
	void ImpactsEffect(const CEffectData& effectData);
	void LBYProxy(const CRecvProxyData* data, void* ent, void* out);
	void DidSmokeEffectProxy(const CRecvProxyData* data, void* ent, void* out);
}

#endif
