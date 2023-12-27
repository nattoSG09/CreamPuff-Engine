#pragma once

// 安全にReleaseするためのマクロ
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

// 安全にdeleteするためのマクロ
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}