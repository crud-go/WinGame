#include "UserInput.h"

KeyStatus UserInput::m_KeyboardState[256] = {0};
bool UserInput::m_KeyNewState[256] = {0};
bool UserInput::m_KeyOldState[256] = {0};

void UserInput::UpdataKeyStatus(UINT key, bool status)
{
  m_KeyNewState[key] = status;
}

void UserInput::Updata()
{
	for (auto i = 0; i < 256; i++)
	{
		if (m_KeyNewState[i] != m_KeyOldState[i])
		{
			if (m_KeyNewState[i] == true)
			{
				m_KeyboardState[i].isHold = true;
				m_KeyboardState[i].isPress = true;
			}
			else
			{
				m_KeyboardState[i].isHold = false;
				m_KeyboardState[i].isRelease = true;
			}
			m_KeyOldState[i] =m_KeyNewState[i];
		}
		else
		{
				if (m_KeyboardState[i].isPress == true) m_KeyboardState[i].isPress = false;
				if (m_KeyboardState[i].isRelease == true) m_KeyboardState[i].isRelease = false;
		}
	}
}

 KeyStatus* UserInput::GetKeyStatus(Key key)
{
	 return &m_KeyboardState[key];
}
