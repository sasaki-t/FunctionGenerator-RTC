// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  FunctionGeneratorTest.cpp
 * @brief Function generator compornent for generating input data (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#include "FunctionGeneratorTest.h"

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const functiongenerator_spec[] =
#else
static const char* functiongenerator_spec[] =
#endif
  {
    "implementation_id", "FunctionGeneratorTest",
    "type_name",         "FunctionGeneratorTest",
    "description",       "Function generator compornent for generating input data",
    "version",           "1.3.0",
    "vendor",            "TakeshiSasaki",
    "category",          "generic",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.xMin", "0.0",
    "conf.default.xMax", "10.0",
    "conf.default.xDelta", "1.0",
    "conf.default.tMin", "0.0",
    "conf.default.tMax", "10.0",
    "conf.default.tDelta", "1.0",
    "conf.default.saveFileMode", "a",
    "conf.default.saveFileName", "*",
    "conf.default.outputFunctionOrLoadFileName", "*",

    // Widget
    "conf.__widget__.xMin", "text",
    "conf.__widget__.xMax", "text",
    "conf.__widget__.xDelta", "text",
    "conf.__widget__.tMin", "text",
    "conf.__widget__.tMax", "text",
    "conf.__widget__.tDelta", "text",
    "conf.__widget__.saveFileMode", "radio",
    "conf.__widget__.saveFileName", "text",
    "conf.__widget__.outputFunctionOrLoadFileName", "text",
    // Constraints
    "conf.__constraints__.saveFileMode", "(a,w)",

    "conf.__type__.xMin", "double",
    "conf.__type__.xMax", "double",
    "conf.__type__.xDelta", "double",
    "conf.__type__.tMin", "double",
    "conf.__type__.tMax", "double",
    "conf.__type__.tDelta", "double",
    "conf.__type__.saveFileMode", "char",
    "conf.__type__.saveFileName", "string",
    "conf.__type__.outputFunctionOrLoadFileName", "string",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
FunctionGeneratorTest::FunctionGeneratorTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_iOctetSeqDataOut("iOctetSeqData", m_iOctetSeqData),
    m_iShortSeqDataOut("iShortSeqData", m_iShortSeqData),
    m_iLongSeqDataOut("iLongSeqData", m_iLongSeqData),
    m_iFloatSeqDataOut("iFloatSeqData", m_iFloatSeqData),
    m_iDoubleSeqDataOut("iDoubleSeqData", m_iDoubleSeqData),
    m_oOctetSeqDataIn("oOctetSeqData", m_oOctetSeqData),
    m_oShortSeqDataIn("oShortSeqData", m_oShortSeqData),
    m_oLongSeqDataIn("oLongSeqData", m_oLongSeqData),
    m_oFloatSeqDataIn("oFloatSeqData", m_oFloatSeqData),
    m_oDoubleSeqDataIn("oDoubleSeqData", m_oDoubleSeqData)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
FunctionGeneratorTest::~FunctionGeneratorTest()
{
}



RTC::ReturnCode_t FunctionGeneratorTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("oOctetSeqData", m_oOctetSeqDataIn);
  addInPort("oShortSeqData", m_oShortSeqDataIn);
  addInPort("oLongSeqData", m_oLongSeqDataIn);
  addInPort("oFloatSeqData", m_oFloatSeqDataIn);
  addInPort("oDoubleSeqData", m_oDoubleSeqDataIn);
  
  // Set OutPort buffer
  addOutPort("iOctetSeqData", m_iOctetSeqDataOut);
  addOutPort("iShortSeqData", m_iShortSeqDataOut);
  addOutPort("iLongSeqData", m_iLongSeqDataOut);
  addOutPort("iFloatSeqData", m_iFloatSeqDataOut);
  addOutPort("iDoubleSeqData", m_iDoubleSeqDataOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("xMin", m_xMin, "0.0");
  bindParameter("xMax", m_xMax, "10.0");
  bindParameter("xDelta", m_xDelta, "1.0");
  bindParameter("tMin", m_tMin, "0.0");
  bindParameter("tMax", m_tMax, "10.0");
  bindParameter("tDelta", m_tDelta, "1.0");
  bindParameter("saveFileMode", m_saveFileMode, "a");
  bindParameter("saveFileName", m_saveFileName, "*");
  bindParameter("outputFunctionOrLoadFileName", m_outputFunctionOrLoadFileName, "*");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t FunctionGeneratorTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/


//RTC::ReturnCode_t FunctionGeneratorTest::onStartup(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t FunctionGeneratorTest::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t FunctionGeneratorTest::onActivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t FunctionGeneratorTest::onDeactivated(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

/*!
 * 各種パラメータの読込みと設定を行う。
 * InPortに送られてきたデータを、ConfigurationのsaveFileModeの形式
 * にしたがって、saveFileNameに指定されたファイルに保存する。
 * ConfigurationのoutputFunctionOrLoadFileNameに指定された関数また
 * はファイルからデータを生成し、OutPortに出力する。
 */

RTC::ReturnCode_t FunctionGeneratorTest::onExecute(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t FunctionGeneratorTest::onAborting(RTC::UniqueId /*ec_id*/)
{
  return RTC::RTC_OK;
}


//RTC::ReturnCode_t FunctionGeneratorTest::onError(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t FunctionGeneratorTest::onReset(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t FunctionGeneratorTest::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


//RTC::ReturnCode_t FunctionGeneratorTest::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//  return RTC::RTC_OK;
//}


bool FunctionGeneratorTest::runTest()
{
    return true;
}


extern "C"
{
 
  void FunctionGeneratorTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(functiongenerator_spec);
    manager->registerFactory(profile,
                             RTC::Create<FunctionGeneratorTest>,
                             RTC::Delete<FunctionGeneratorTest>);
  }
  
}
