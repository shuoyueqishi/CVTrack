#ifndef TEST_APP_UTILS_H
#define TEST_APP_UTILS_H

#define THROW_ON_ERROR(x) \
{ \
    smReturnCode result = (x); \
    if (result < 0) \
    { \
        std::stringstream s; \
        s << "API error code: " << result; \
        throw std::runtime_error(s.str()); \
    } \
}

unsigned short g_overlay_flags(SM_API_VIDEO_DISPLAY_HEAD_MESH);

void toggleFlag(unsigned short &val, unsigned short flag)
            {
                if (val & flag)
                {
                    val = val & ~flag;
                }
                else
                {
                    val = val | flag;
                }
            }

float rad2deg(float rad)
{
	return rad*57.2957795f;
}

// Handles messages generated by API routines
void STDCALL receiveLogMessage(void *, const char *buf, int buf_len)
{
    std::cerr << std::string(buf);
}

bool processKeyPress(smEngineHandle engine, smVideoDisplayHandle video_display_handle)
{
    if (!_kbhit())
    {
        return true;
    }
    int key = _getch();
    switch (key)
    {
    case 'r':
        {
            // Manually restart the tracking
            THROW_ON_ERROR(smEngineStart(engine));
        }
        return true;
    case 'a':
        {
            // Toggle auto-restart mode
            int on;
            THROW_ON_ERROR(smHTGetAutoRestartMode(engine,&on));
            THROW_ON_ERROR(smHTSetAutoRestartMode(engine,!on));
        }
        return true;
    
    
    case '2':
        printf("WHAAAAT?\n");
                toggleFlag(g_overlay_flags,SM_API_VIDEO_DISPLAY_PERFORMANCE);
                THROW_ON_ERROR(smVideoDisplaySetFlags(video_display_handle,g_overlay_flags));
                return true;
    default:
        return false;
    }
}

#endif
