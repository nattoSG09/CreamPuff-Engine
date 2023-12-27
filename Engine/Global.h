#pragma once

// ���S��Release���邽�߂̃}�N��
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

// ���S��delete���邽�߂̃}�N��
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}