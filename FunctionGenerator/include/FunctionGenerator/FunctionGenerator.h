﻿// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  FunctionGenerator.h
 * @brief Function generator compornent for generating input data
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 */
// </rtc-template>

#ifndef FUNCTIONGENERATOR_H
#define FUNCTIONGENERATOR_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
#include <cmath>

#include "math_function_generator.h"
#include "convert.h"

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>


// <rtc-template block="component_description">
/*!
 * @class FunctionGenerator
 * @brief Function generator compornent for generating input data
 *
 * 数学関数や事前に保存したデータ列を指定することで様々なパターンの
 * 入力データを生成することが可能な入力データ生成コンポーネント。
 * コンフィギュレーションパラメータから出力したいデータを数学関数に
 * よって指定することが可能。
 * また、InPortに入力されたデータを記録する機能を備えているため、予
 * め保存したデータを読み込んで出力することも可能。
 *
 * InPort
 * ポート名/型/説明
 * iOctetSeqData/TimedOctetSeq/ファイルに保存するoctet型数値列デー
 * タ。
 * iShortSeqData/TimedShortSeq/ファイルに保存するshort型整数値列デ
 * ータ。
 * iLongSeqData/TimedLongSeq/ファイルに保存するlong型整数値列データ
 * 。
 * iFloatSeqData/TimedFloatSeq/ファイルに保存するfloat型実数値列デ
 * ータ。
 * iDoubleSeqData/TimedDoubleSeq/ファイルに保存するdouble型実数値列
 * データ。
 * OutPort
 * ポート名/型/説明
 * oOctetSeqData/TimedOctetSeq/octet型数値列の出力データ。
 * oShortSeqData/TimedShortSeq/short型整数値列の出力データ。
 * oLongSeqData/TimedLongSeq/long型整数値列の出力データ。
 * oFloatSeqData/TimedFloatSeq/float型実数値列の出力データ。
 * oDoubleSeqData/TimedDoubleSeq/double型実数値列の出力データ。
 *
 */
// </rtc-template>
class FunctionGenerator
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  FunctionGenerator(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~FunctionGenerator() override;

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
  RTC::TimedOctetSeq m_iOctetSeqData;
  /*!
   * ファイルに保存するoctet型数値列データ。
   * - Type: TimedOctetSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedOctetSeq> m_iOctetSeqDataIn;
  RTC::TimedShortSeq m_iShortSeqData;
  /*!
   * ファイルに保存するshort型整数値列データ。
   * - Type: TimedShortSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedShortSeq> m_iShortSeqDataIn;
  RTC::TimedLongSeq m_iLongSeqData;
  /*!
   * ファイルに保存するlong型整数値列データ。
   * - Type: TimedLongSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedLongSeq> m_iLongSeqDataIn;
  RTC::TimedFloatSeq m_iFloatSeqData;
  /*!
   * ファイルに保存するfloat型実数値列データ。
   * - Type: TimedFloatSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedFloatSeq> m_iFloatSeqDataIn;
  RTC::TimedDoubleSeq m_iDoubleSeqData;
  /*!
   * ファイルに保存するdouble型実数値列データ。
   * - Type: TimedDoubleSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::InPort<RTC::TimedDoubleSeq> m_iDoubleSeqDataIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedOctetSeq m_oOctetSeqData;
  /*!
   * octet型数値列の出力データ。
   * - Type: TimedOctetSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedOctetSeq> m_oOctetSeqDataOut;
  RTC::TimedShortSeq m_oShortSeqData;
  /*!
   * short型整数値列の出力データ。
   * - Type: TimedShortSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedShortSeq> m_oShortSeqDataOut;
  RTC::TimedLongSeq m_oLongSeqData;
  /*!
   * long型整数値列の出力データ。
   * - Type: TimedLongSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedLongSeq> m_oLongSeqDataOut;
  RTC::TimedFloatSeq m_oFloatSeqData;
  /*!
   * float型実数値列の出力データ。
   * - Type: TimedFloatSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedFloatSeq> m_oFloatSeqDataOut;
  RTC::TimedDoubleSeq m_oDoubleSeqData;
  /*!
   * double型実数値列の出力データ。
   * - Type: TimedDoubleSeq
   * - Number: データに依存
   * - Unit: データに依存
   */
  RTC::OutPort<RTC::TimedDoubleSeq> m_oDoubleSeqDataOut;
  
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
	std::string cmd; //current command
	int operation_mode; //0:function output mode, 1:file output mode

	//for function output mode
	MathFunctionGenerator mfg; //math function generator

	//for file output mode
	//save file
	std::ofstream outfile; //file for storing input data
	char s_file_mode; //save file mode - w:overwrite, a:append
	std::string s_file_name; //name of the save file
	//load file
	std::ifstream infile; //file for loading previously stored data
	std::string l_filename; //name of the load file

  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void FunctionGeneratorInit(RTC::Manager* manager);
};

#endif // FUNCTIONGENERATOR_H
