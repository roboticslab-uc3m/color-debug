// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <ColorDebug.h>

int main(int argc, char *argv[])
{
    CD_ERROR("Example CD_ERROR.\n");
    CD_WARNING("Example CD_WARNING.\n");
    CD_SUCCESS("Example CD_SUCCESS.\n");
    CD_INFO("Example CD_INFO.\n");
    CD_DEBUG("Example CD_DEBUG.\n\n");

    CD_ERROR_NO_HEADER("Example CD_ERROR_NO_HEADER.\n");
    CD_WARNING_NO_HEADER("Example CD_WARNING_NO_HEADER.\n");
    CD_SUCCESS_NO_HEADER("Example CD_SUCCESS_NO_HEADER.\n");
    CD_INFO_NO_HEADER("Example CD_INFO_NO_HEADER.\n");
    CD_DEBUG_NO_HEADER("Example CD_DEBUG_NO_HEADER.\n\n");

    return 0;
}
