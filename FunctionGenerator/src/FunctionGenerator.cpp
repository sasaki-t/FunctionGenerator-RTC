// -*- C++ -*-
/*!
 * @file  FunctionGenerator.cpp
 * @brief Function generator compornent for generating input data
 * @date $Date$
 *
 * @author 佐々木毅 (Takeshi SASAKI)
 * sasaki-t(_at_)ieee.org
 *
 * $Id$
 */

#include "FunctionGenerator.h"

// Module specification
// <rtc-template block="module_spec">
static const char* functiongenerator_spec[] =
  {
    "implementation_id", "FunctionGenerator",
    "type_name",         "FunctionGenerator",
    "description",       "Function generator compornent for generating input data",
    "version",           "1.2.0",
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
    "conf.__constraints__.saveFileMode", "(a, w)",

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
FunctionGenerator::FunctionGenerator(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_iOctetSeqDataIn("iOctetSeqData", m_iOctetSeqData),
    m_iShortSeqDataIn("iShortSeqData", m_iShortSeqData),
    m_iLongSeqDataIn("iLongSeqData", m_iLongSeqData),
    m_iFloatSeqDataIn("iFloatSeqData", m_iFloatSeqData),
    m_iDoubleSeqDataIn("iDoubleSeqData", m_iDoubleSeqData),
    m_oOctetSeqDataOut("oOctetSeqData", m_oOctetSeqData),
    m_oShortSeqDataOut("oShortSeqData", m_oShortSeqData),
    m_oLongSeqDataOut("oLongSeqData", m_oLongSeqData),
    m_oFloatSeqDataOut("oFloatSeqData", m_oFloatSeqData),
    m_oDoubleSeqDataOut("oDoubleSeqData", m_oDoubleSeqData)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
FunctionGenerator::~FunctionGenerator()
{
	if (infile.is_open()) {
		infile.close();
	}
	if (outfile.is_open()) {
		outfile.close();
	}
}



RTC::ReturnCode_t FunctionGenerator::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("iOctetSeqData", m_iOctetSeqDataIn);
  addInPort("iShortSeqData", m_iShortSeqDataIn);
  addInPort("iLongSeqData", m_iLongSeqDataIn);
  addInPort("iFloatSeqData", m_iFloatSeqDataIn);
  addInPort("iDoubleSeqData", m_iDoubleSeqDataIn);
  
  // Set OutPort buffer
  addOutPort("oOctetSeqData", m_oOctetSeqDataOut);
  addOutPort("oShortSeqData", m_oShortSeqDataOut);
  addOutPort("oLongSeqData", m_oLongSeqDataOut);
  addOutPort("oFloatSeqData", m_oFloatSeqDataOut);
  addOutPort("oDoubleSeqData", m_oDoubleSeqDataOut);
  
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
RTC::ReturnCode_t FunctionGenerator::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FunctionGenerator::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FunctionGenerator::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * 初期化を行う。
 */

RTC::ReturnCode_t FunctionGenerator::onActivated(RTC::UniqueId ec_id)
{
	int res;

	m_iOctetSeqDataIn.read();
	m_iShortSeqDataIn.read();
	m_iLongSeqDataIn.read();
	m_iFloatSeqDataIn.read();
	m_iDoubleSeqDataIn.read();

	res = mfg.initialize();
	if (res != 0) {
		return RTC::RTC_ERROR;
	}

	operation_mode = -1;
	cmd.clear();
	s_file_mode = 'a';
	s_file_name.clear();
	l_filename.clear();

	return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t FunctionGenerator::onDeactivated(RTC::UniqueId ec_id)
{
	if (infile.is_open()) {
		infile.close();
	}
	if (outfile.is_open()) {
		outfile.close();
	}

	return RTC::RTC_OK;
}

/*!
 * 各種パラメータの読込みと設定を行う。
 * InPortに送られてきたデータを、ConfigurationのsaveFileModeの形式
 * にしたがって、saveFileNameに指定されたファイルに保存する。
 * ConfigurationのoutputFunctionOrLoadFileNameに指定された関数また
 * はファイルからデータを生成し、OutPortに出力する。
 */

RTC::ReturnCode_t FunctionGenerator::onExecute(RTC::UniqueId ec_id)
{
	int res;
	unsigned int i;
	unsigned int data_length;
	std::string st;
	std::string::size_type loc;

	//list for storing the obtained data
	std::list<double> output_data_list;
	std::list<double>::iterator it;


	// ***** Save input data to file ********** /
	// ----- set file parameters -------------- /
	if (((m_saveFileMode != s_file_mode) || (m_saveFileName != s_file_name)) && (m_saveFileName != "*") && (!m_saveFileName.empty())) { //parameter changed && valid data
		st = m_saveFileName;
		char md = m_saveFileMode;

		//check the extension
		loc = st.find_last_of('.');
		if ((loc == std::string::npos) || ((st.substr(loc) != ".txt") && (st.substr(loc) != ".csv") && (st.substr(loc) != ".dat"))) { //no valid extensions
			st += ".txt";
		}

		//close file if opened
		if (outfile.is_open()) {
			outfile.close();
		}

		if (md == 'a') {
			outfile.open(st.c_str(), std::ios::app);
			if (!outfile) {
				std::cerr << "Cannot open file:" << st.c_str() << std::endl;
			}
			else {
				std::cerr << "File opened:" << st.c_str() << std::endl;
				s_file_mode = md;
				s_file_name = m_saveFileName;
			}
		}
		else if (md == 'w') {
			outfile.open(st.c_str(), std::ios::out);
			if (!outfile) {
				std::cerr << "Cannot open file:" << st.c_str() << std::endl;
			}
			else {
				std::cerr << "File opened:" << st.c_str() << std::endl;
				s_file_mode = md;
				s_file_name = m_saveFileName;
			}
		}
		else {
			std::cerr << "Invalid parameter: saveFileMode" << std::endl;
		}
	}

	// ----- save input data to file -------------- /
	//if data comes to the InPorts, then store the data
	//OctetSeq data
	if (m_iOctetSeqDataIn.isNew()) {
		m_iOctetSeqDataIn.read();
		if (outfile.is_open()) {
			data_length = m_iOctetSeqData.data.length();
			for (i = 0; i < data_length; i++) {
				outfile << (int)m_iOctetSeqData.data[i] << std::endl;
			}
			outfile << std::endl;
		}
		else {
			std::cerr << "Cannot save input data: file not opened." << std::endl;
		}
	}

	//ShortSeq data
	if (m_iShortSeqDataIn.isNew()) {
		m_iShortSeqDataIn.read();
		if (outfile.is_open()) {
			data_length = m_iShortSeqData.data.length();
			for (i = 0; i < data_length; i++) {
				outfile << m_iShortSeqData.data[i] << std::endl;
			}
			outfile << std::endl;
		}
		else {
			std::cerr << "Cannot save input data: file not opened." << std::endl;
		}
	}

	//LongSeq data
	if (m_iLongSeqDataIn.isNew()) {
		m_iLongSeqDataIn.read();
		if (outfile.is_open()) {
			data_length = m_iLongSeqData.data.length();
			for (i = 0; i < data_length; i++) {
				outfile << m_iLongSeqData.data[i] << std::endl;
			}
			outfile << std::endl;
		}
		else {
			std::cerr << "Cannot save input data: file not opened." << std::endl;
		}
	}

	//FloatSeq data
	if (m_iFloatSeqDataIn.isNew()) {
		m_iFloatSeqDataIn.read();
		if (outfile.is_open()) {
			data_length = m_iFloatSeqData.data.length();
			for (i = 0; i < data_length; i++) {
				outfile << m_iFloatSeqData.data[i] << std::endl;
			}
			outfile << std::endl;
		}
		else {
			std::cerr << "Cannot save input data: file not opened." << std::endl;
		}
	}

	//DoubleSeq data
	if (m_iDoubleSeqDataIn.isNew()) {
		m_iDoubleSeqDataIn.read();
		if (outfile.is_open()) {
			data_length = m_iDoubleSeqData.data.length();
			for (i = 0; i < data_length; i++) {
				outfile << m_iDoubleSeqData.data[i] << std::endl;
			}
			outfile << std::endl;
		}
		else {
			std::cerr << "Cannot save input data: file not opened." << std::endl;
		}
	}
	// ***** End save input data to file ********** /


	// ***** Set output parameters ********** /
	//get function or load file name
	if ((m_outputFunctionOrLoadFileName != cmd) && (m_outputFunctionOrLoadFileName != "*") && (!m_outputFunctionOrLoadFileName.empty())) {
		st = m_outputFunctionOrLoadFileName;

		//check the extension
		loc = st.find_last_of('.');
		if ((loc == std::string::npos) || ((st.substr(loc) != ".txt") && (st.substr(loc) != ".csv") && (st.substr(loc) != ".dat"))) { //no valid extensions
		  //set function
			res = mfg.getFunction(st);
			if (res == 0) {
				std::cerr << "Set command:" << st.c_str() << std::endl;
				cmd = st;
				operation_mode = 0; //function output mode
			}
			else {
				operation_mode = -1;
			}
		}
		else {
			//set filename
			//close file if opened
			if (infile.is_open()) {
				infile.close();
			}

			infile.open(st.c_str(), std::ios::in);
			if (!infile) {
				std::cerr << "Cannot open file:" << st.c_str() << std::endl;
				operation_mode = -1;
			}
			else {
				std::cerr << "File opened:" << st.c_str() << std::endl;
				cmd = st;
				operation_mode = 1; //file output mode
			}
		}
	}

	if (operation_mode == 0) {
		//set variable parameters
		if (m_xMin != mfg.getXMin() || m_xMax != mfg.getXMax() || m_xDelta != mfg.getXDelta()) {
			res = mfg.setXParams(m_xMin, m_xMax, m_xDelta);
			if (res != 0) {
				return RTC::RTC_OK;
			}
		}
		if (m_tMin != mfg.getTMin() || m_tMax != mfg.getTMax() || m_tDelta != mfg.getTDelta()) {
			res = mfg.setTParams(m_tMin, m_tMax, m_tDelta);
			if (res != 0) {
				return RTC::RTC_OK;
			}
		}
	}


	// ***** Get data ********** /
	if (operation_mode == 0) {
		res = mfg.putFunction(output_data_list);
		if (res > 0) {
			return RTC::RTC_OK;
		}
	}
	else if (operation_mode == 1) {
		if (!infile.is_open()) {
			return RTC::RTC_OK;
		}

		//Read file
		bool is_once_read = false;
		bool is_loop = false;
		for (;;) { //for each line
			getline(infile, st);
			if (st.empty()) { //newline code only
				if (is_once_read) { //data has already been obtained
					break;
				}
				else if (infile.eof()) { //no more data
					if (is_loop) {
						break;
					}
					else {
						is_loop = true;
						// Reset the read pointer to the beginning of the file
						infile.clear(); //need to call this function since seekg() does NOT reset the EOF state
						infile.seekg(0, std::ios::beg);
						continue;
					}
				}
				else { //data has not obtained yet
					continue;
				}
			}

			is_once_read = true;
			std::string::size_type loc_tmp = 0;
			for (;;) { //for each data
				loc = st.substr(loc_tmp).find_first_of(", \t");
				if (loc != 0) {
					std::string str_tmp = st.substr(loc_tmp, loc);
					output_data_list.push_back(std::atof(str_tmp.c_str()));
				}

				if (loc == std::string::npos) { //no more separators
					break;
				}
				else {
					loc_tmp += loc + 1; //update search starting position
					if (st.substr(loc_tmp).empty()) { break; }
				}
			}//end for(each data)
		}//end for(each line)
		if (infile.eof()) {
			// Reset the read pointer to the beginning of the file
			infile.clear(); //need to call this function since seekg() does NOT reset the EOF state
			infile.seekg(0, std::ios::beg);
		}

	}
	else { //No operation mode set
		return RTC::RTC_OK;
	} //end if(operation_mode)


	// ***** Output data to OutPorts ********** /
	//set the data length
	data_length = output_data_list.size();
	if (data_length == 0) {
		std::cerr << "No data obtatined" << std::endl;
		return RTC::RTC_OK;
	}

	m_oOctetSeqData.data.length(data_length);
	m_oShortSeqData.data.length(data_length);
	m_oLongSeqData.data.length(data_length);
	m_oFloatSeqData.data.length(data_length);
	m_oDoubleSeqData.data.length(data_length);

	//store the data to the buffers
	it = output_data_list.begin();
	for (i = 0; i < data_length; i++) {
		m_oOctetSeqData.data[i] = (CORBA::Octet)toUInt8(*it);
		m_oShortSeqData.data[i] = (CORBA::Short)toInt16(*it);
		m_oLongSeqData.data[i] = (CORBA::Long)toInt32(*it);
		m_oFloatSeqData.data[i] = toFloat(*it);
		m_oDoubleSeqData.data[i] = *it;

		it++;
	} //end for(i)

	//store the time data
	setTimestamp(m_oOctetSeqData);
	setTimestamp(m_oShortSeqData);
	setTimestamp(m_oLongSeqData);
	setTimestamp(m_oFloatSeqData);
	setTimestamp(m_oDoubleSeqData);

	//output the data
	m_oOctetSeqDataOut.write();
	m_oShortSeqDataOut.write();
	m_oLongSeqDataOut.write();
	m_oFloatSeqDataOut.write();
	m_oDoubleSeqDataOut.write();

#ifdef _DEBUG
	// for debug -- print the output data
  /*
	it = output_data_list.begin();
	std::cout << "Output data: " << std::flush;
	while(it != output_data_list.end()){
	  std::cout << (*it) << ' ' << std::flush;
	  it++;
	}
	std::cout << std::endl;
  */

	std::cout << "octet:" << std::flush;
	for (i = 0; i < data_length; i++) {
		std::cout << (int)m_oOctetSeqData.data[i] << ' ' << std::flush;
	}
	std::cout << std::endl;

	std::cout << "short:" << std::flush;
	for (i = 0; i < data_length; i++) {
		std::cout << m_oShortSeqData.data[i] << ' ' << std::flush;
	}
	std::cout << std::endl;

	std::cout << "long:" << std::flush;
	for (i = 0; i < data_length; i++) {
		std::cout << m_oLongSeqData.data[i] << ' ' << std::flush;
	}
	std::cout << std::endl;

	std::cout << "float:" << std::flush;
	for (i = 0; i < data_length; i++) {
		std::cout << m_oFloatSeqData.data[i] << ' ' << std::flush;
	}
	std::cout << std::endl;

	std::cout << "double:" << std::flush;
	for (i = 0; i < data_length; i++) {
		std::cout << m_oDoubleSeqData.data[i] << ' ' << std::flush;
	}
	std::cout << std::endl;

	std::cout << std::endl;
#endif
	
	return RTC::RTC_OK;
}

/*!
 * 終了処理を行う。
 */

RTC::ReturnCode_t FunctionGenerator::onAborting(RTC::UniqueId ec_id)
{
	if (infile.is_open()) {
		infile.close();
	}
	if (outfile.is_open()) {
		outfile.close();
	}

	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t FunctionGenerator::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FunctionGenerator::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FunctionGenerator::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t FunctionGenerator::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void FunctionGeneratorInit(RTC::Manager* manager)
  {
    coil::Properties profile(functiongenerator_spec);
    manager->registerFactory(profile,
                             RTC::Create<FunctionGenerator>,
                             RTC::Delete<FunctionGenerator>);
  }
  
};


