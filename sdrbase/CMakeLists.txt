project (sdrbase)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

set(sdrbase_SOURCES
    audio/audiocompressor.cpp
    audio/audiodevicemanager.cpp
    audio/audiofifo.cpp
    audio/audiofilter.cpp
    audio/audiooutput.cpp
    audio/audioinput.cpp
    audio/audionetsink.cpp

    channel/channelsinkapi.cpp
    channel/channelsourceapi.cpp
    channel/remotedataqueue.cpp
    channel/remotedatareadqueue.cpp

    commands/command.cpp

    dsp/afsquelch.cpp
    dsp/agc.cpp
    dsp/downchannelizer.cpp
    dsp/upchannelizer.cpp
    dsp/channelmarker.cpp
    dsp/ctcssdetector.cpp
    dsp/cwkeyer.cpp
    dsp/cwkeyersettings.cpp
    dsp/decimatorsif.cpp
    dsp/decimatorsff.cpp
    dsp/decimatorsfi.cpp
    dsp/dspcommands.cpp
    dsp/dspengine.cpp
    dsp/dspdevicesourceengine.cpp
    dsp/dspdevicesinkengine.cpp
    dsp/fftcorr.cpp
    dsp/fftengine.cpp
    dsp/fftfilt.cpp
    dsp/fftwindow.cpp
    dsp/filterrc.cpp
    dsp/filtermbe.cpp
    dsp/filerecord.cpp
    dsp/freqlockcomplex.cpp
    dsp/interpolator.cpp
    dsp/hbfiltertraits.cpp
    dsp/lowpass.cpp
    dsp/nco.cpp
    dsp/ncof.cpp
    dsp/phaselock.cpp
    dsp/phaselockcomplex.cpp
    dsp/projector.cpp
    dsp/samplesinkfifo.cpp
    dsp/samplesourcefifo.cpp
    dsp/samplesinkfifodoublebuffered.cpp
    dsp/basebandsamplesink.cpp
    dsp/basebandsamplesource.cpp
    dsp/nullsink.cpp
    dsp/recursivefilters.cpp
    dsp/threadedbasebandsamplesink.cpp
    dsp/threadedbasebandsamplesource.cpp
    dsp/wfir.cpp
    dsp/devicesamplesource.cpp
    dsp/devicesamplesink.cpp

    device/devicesourceapi.cpp
    device/devicesinkapi.cpp
    device/deviceenumerator.cpp

    settings/preferences.cpp
    settings/preset.cpp
    settings/mainsettings.cpp

    util/CRC64.cpp
    util/db.cpp
    util/fixedtraits.cpp
    util/message.cpp
    util/messagequeue.cpp
    util/prettyprint.cpp
    util/rtpsink.cpp
    util/syncmessenger.cpp
    util/samplesourceserializer.cpp
    util/simpleserializer.cpp
    #util/spinlock.cpp
    util/uid.cpp
    util/timeutil.cpp

    plugin/plugininterface.cpp
    plugin/pluginapi.cpp
    plugin/pluginmanager.cpp

    webapi/webapiadapterinterface.cpp
    webapi/webapirequestmapper.cpp
    webapi/webapiserver.cpp

    mainparser.cpp
)

set(sdrbase_HEADERS
	audio/audiocompressor.h
    audio/audiodevicemanager.h
    audio/audiofifo.h
    audio/audiofilter.h
    audio/audiooutput.h
    audio/audioinput.h
    audio/audionetsink.h

    channel/channelsinkapi.h
    channel/channelsourceapi.h
    channel/remotedataqueue.h
    channel/remotedatareadqueue.h
    channel/remotedatablock.h

    commands/command.h

    dsp/afsquelch.h
    dsp/autocorrector.h
    dsp/downchannelizer.h
    dsp/upchannelizer.h
    dsp/channelmarker.h
    dsp/complex.h
    dsp/cwkeyer.h
    dsp/cwkeyersettings.h
    dsp/decimators.h
    dsp/decimatorsif.h
    dsp/decimatorsff.h
    dsp/decimatorsfi.h
    dsp/decimatorsu.h
    dsp/interpolators.h
    dsp/dspcommands.h
    dsp/dspengine.h
    dsp/dspdevicesourceengine.h
    dsp/dspdevicesinkengine.h
    dsp/dsptypes.h
    dsp/fftcorr.h
    dsp/fftengine.h
    dsp/fftfilt.h
    dsp/fftwengine.h
    dsp/fftwindow.h
    dsp/filterrc.h
    dsp/filtermbe.h
    dsp/filerecord.h
    dsp/freqlockcomplex.h
    dsp/gfft.h
    dsp/iirfilter.h
    dsp/interpolator.h
    dsp/hbfiltertraits.h
    dsp/inthalfbandfilter.h
    dsp/inthalfbandfilterdb.h
    dsp/inthalfbandfilterdbf.h
    dsp/inthalfbandfiltereo.h
    # dsp/inthalfbandfiltereo1.h
    # dsp/inthalfbandfiltereo1i.h
    # dsp/inthalfbandfiltereo2.h
    dsp/inthalfbandfiltereof.h
    dsp/inthalfbandfilterst.h
    dsp/inthalfbandfiltersti.h
    dsp/kissfft.h
    dsp/kissengine.h
    dsp/lowpass.h
    dsp/misc.h
    dsp/movingaverage.h
    dsp/nco.h
    dsp/ncof.h
    dsp/phasediscri.h
    dsp/phaselock.h
    dsp/phaselockcomplex.h
    dsp/projector.h
    dsp/recursivefilters.h
    dsp/samplesinkfifo.h
    dsp/samplesourcefifo.h
    dsp/samplesinkfifodoublebuffered.h
    dsp/samplesinkfifodecimator.h
    dsp/basebandsamplesink.h
    dsp/basebandsamplesource.h
    dsp/nullsink.h
    dsp/threadedbasebandsamplesink.h
    dsp/threadedbasebandsamplesource.h
    dsp/wfir.h
    dsp/devicesamplesource.h
    dsp/devicesamplesink.h

    device/devicesourceapi.h
    device/devicesinkapi.h
    device/deviceenumerator.h

    plugin/plugininstancegui.h
    plugin/plugininterface.h
    plugin/pluginapi.h
    plugin/pluginmanager.h

    settings/preferences.h
    settings/preset.h
    settings/mainsettings.h

    util/CRC64.h
    util/db.h
    util/doublebuffer.h
    util/doublebufferfifo.h
    util/fixedtraits.h
    util/message.h
    util/messagequeue.h
    util/movingaverage.h
    util/prettyprint.h
    util/rtpsink.h
    util/syncmessenger.h
    util/samplesourceserializer.h
    util/simpleserializer.h
    #util/spinlock.h
    util/uid.h
    util/timeutil.h

    webapi/webapiadapterinterface.h
    webapi/webapirequestmapper.h
    webapi/webapiserver

    mainparser.h
)

set(sdrbase_SOURCES
    ${sdrbase_SOURCES}
    ${sdrbase_HEADERS}
)

if(FFTW3F_FOUND)
    set(sdrbase_SOURCES
        ${sdrbase_SOURCES}
        dsp/fftwengine.cpp
    )
    set(sdrbase_HEADERS
        ${sdrbase_HEADERS}
        dsp/fftwengine.h
    )
    add_definitions(-DUSE_FFTW)
    include_directories(${FFTW3F_INCLUDE_DIRS})
else(FFTW3F_FOUND)
    set(sdrbase_SOURCES
        ${sdrbase_SOURCES}
        dsp/kissengine.cpp
        dsp/kissfft.h
    )
    set(sdrbase_HEADERS
        ${sdrbase_HEADERS}
        dsp/kissengine.h
    )
    add_definitions(-DUSE_KISSFFT)
endif(FFTW3F_FOUND)

if (LIBSERIALDV_FOUND)
    set(sdrbase_SOURCES
        ${sdrbase_SOURCES}
        dsp/dvserialworker.cpp
        dsp/dvserialengine.cpp
    )
    set(sdrbase_HEADERS
        ${sdrbase_HEADERS}
        dsp/dvserialworker.h
        dsp/dvserialengine.h
    )
    message(STATUS "Will have SerialDV support")
    add_definitions(-DDSD_USE_SERIALDV)
    include_directories(${LIBSERIALDV_INCLUDE_DIR})
else(LIBSERIALDV_FOUND)
    message(STATUS "No SerialDV support")
endif(LIBSERIALDV_FOUND)

if (BUILD_DEBIAN)
    set(sdrbase_SOURCES
        ${sdrbase_SOURCES}
        dsp/dvserialworker.cpp
        dsp/dvserialengine.cpp
    )
    set(sdrbase_HEADERS
        ${sdrbase_HEADERS}
        dsp/dvserialworker.h
        dsp/dvserialengine.h
    )
    add_definitions(-DDSD_USE_SERIALDV)
    include_directories(${LIBSERIALDVSRC})
endif (BUILD_DEBIAN)

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)

add_library(sdrbase SHARED
    ${sdrbase_SOURCES}
    ${sdrbase_HEADERS_MOC}
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    .
    ${CMAKE_SOURCE_DIR}/exports
    ${CMAKE_SOURCE_DIR}/httpserver
    ${CMAKE_SOURCE_DIR}/qrtplib
    ${CMAKE_SOURCE_DIR}/swagger/sdrangel/code/qt5/client
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(sdrbase
    ${QT_LIBRARIES}
    httpserver
    qrtplib
    swagger
)

if(FFTW3F_FOUND)
    target_link_libraries(sdrbase ${FFTW3F_LIBRARIES})
endif(FFTW3F_FOUND)

if(LIBSERIALDV_FOUND)
    target_link_libraries(sdrbase ${LIBSERIALDV_LIBRARY})
endif(LIBSERIALDV_FOUND)

if (BUILD_DEBIAN)
    target_link_libraries(sdrbase serialdv)
endif (BUILD_DEBIAN)

set_target_properties(sdrbase PROPERTIES DEFINE_SYMBOL "sdrbase_EXPORTS")
target_compile_features(sdrbase PRIVATE cxx_generalized_initializers) # cmake >= 3.1.0

target_link_libraries(sdrbase Qt5::Core Qt5::Multimedia)

install(TARGETS sdrbase DESTINATION lib)

