// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  FunctionGeneratorTest.h
 * @brief Function generator compornent for generating input data (test code)
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#ifndef FUNCTIONGENERATOR_TEST__H
#define FUNCTIONGENERATOR_TEST_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class FunctionGeneratorTest
 * @brief Function generator compornent for generating input data
 *
 */
class FunctionGeneratorTest
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  FunctionGeneratorTest(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~FunctionGeneratorTest() override;

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  // <rtc-template block="activity">
  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onInitialize() override;

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onFinalize() override;

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id) override;

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id) override;

  /***
   * 初期化を行う。
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id) override;

  /***
   * 終了処理を行う。
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   * 各種パラメータの読込みと設定を行う。
   * InPortに送られてきたデータを、ConfigurationのsaveFileModeの形
   * 式にしたがって、saveFileNameに指定されたファイルに保存する。
   * ConfigurationのoutputFunctionOrLoadFileNameに指定された関数ま
   * たはファイルからデータを生成し、OutPortに出力する。
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

  /***
   * 終了処理を行う。
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id) override;

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onError(RTC::UniqueId ec_id) override;

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onReset(RTC::UniqueId ec_id) override;
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id) override;

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id) override;
  // </rtc-template>

  bool runTest();

 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 変数xの最小値。
   * - Name: xMin xMin
   * - DefaultValue: 0.0
   */
  double m_xMin;
  /*!
   * 変数xの最大値。
   * - Name: xMax xMax
   * - DefaultValue: 10.0
   */
  double m_xMax;
  /*!
   * 変数xの増加量。
   * - Name: xDelta xDelta
   * - DefaultValue: 1.0
   */
  double m_xDelta;
  /*!
   * 変数tの最小値。
   * - Name: tMin tMin
   * - DefaultValue: 0.0
   */
  double m_tMin;
  /*!
   * 変数tの最大値。
   * - Name: tMax tMax
   * - DefaultValue: 10.0
   */
  double m_tMax;
  /*!
   * 変数tの増加量。
   * - Name: tDelta tDelta
   * - DefaultValue: 1.0
   */
  double m_tDelta;
  /*!
   * 入力データを保存するときのモード。
   * a:既存のファイルに追記。
   * w:アクティブ化時またはアクティブ化後のsaveFileMode再設定時に既
   * 存のファイルを上書き。
   * - Name: saveFileMode saveFileMode
   * - DefaultValue: a
   */
  char m_saveFileMode;
  /*!
   * 
   * - Name: saveFileName saveFileName
   * - DefaultValue: *
   */
  std::string m_saveFileName;
  /*!
   * 出力する関数または読み込むファイル名。
   * - Name: outputFunctionOrLoadFileName outputFunctionOrLoadFileName
   * - DefaultValue: *
   */
  std::string m_outputFunctionOrLoadFileName;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedOctetSeq m_oOctetSeqData;
  /*!
   * octet型数値列の出力データ。
   * - Type: TimedOctetSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedOctetSeq> m_oOctetSeqDataIn;
  RTC::TimedShortSeq m_oShortSeqData;
  /*!
   * short型整数値列の出力データ。
   * - Type: TimedShortSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedShortSeq> m_oShortSeqDataIn;
  RTC::TimedLongSeq m_oLongSeqData;
  /*!
   * long型整数値列の出力データ。
   * - Type: TimedLongSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedLongSeq> m_oLongSeqDataIn;
  RTC::TimedFloatSeq m_oFloatSeqData;
  /*!
   * float型実数値列の出力データ。
   * - Type: TimedFloatSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedFloatSeq> m_oFloatSeqDataIn;
  RTC::TimedDoubleSeq m_oDoubleSeqData;
  /*!
   * double型実数値列の出力データ。
   * - Type: TimedDoubleSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedDoubleSeq> m_oDoubleSeqDataIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedOctetSeq m_iOctetSeqData;
  /*!
   * ファイルに保存するoctet型数値列データ。
   * - Type: TimedOctetSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedOctetSeq> m_iOctetSeqDataOut;
  RTC::TimedShortSeq m_iShortSeqData;
  /*!
   * ファイルに保存するshort型整数値列データ。
   * - Type: TimedShortSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedShortSeq> m_iShortSeqDataOut;
  RTC::TimedLongSeq m_iLongSeqData;
  /*!
   * ファイルに保存するlong型整数値列データ。
   * - Type: TimedLongSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedLongSeq> m_iLongSeqDataOut;
  RTC::TimedFloatSeq m_iFloatSeqData;
  /*!
   * ファイルに保存するfloat型実数値列データ。
   * - Type: TimedFloatSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedFloatSeq> m_iFloatSeqDataOut;
  RTC::TimedDoubleSeq m_iDoubleSeqData;
  /*!
   * ファイルに保存するdouble型実数値列データ。
   * - Type: TimedDoubleSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedDoubleSeq> m_iDoubleSeqDataOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void FunctionGeneratorTestInit(RTC::Manager* manager);
};

#endif // FUNCTIONGENERATOR_TEST_H
