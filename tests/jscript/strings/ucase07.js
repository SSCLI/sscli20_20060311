//# ==++== 
//# 
//#   
//#    Copyright (c) 2006 Microsoft Corporation.  All rights reserved.
//#   
//#    The use and distribution terms for this software are contained in the file
//#    named license.txt, which can be found in the root of this distribution.
//#    By using this software in any fashion, you are agreeing to be bound by the
//#    terms of this license.
//#   
//#    You must not remove this notice, or any other, from this software.
//#   
//# 
//# ==--== 
//####################################################################################
@cc_on


import System;

var NULL_DISPATCH = null;
var apGlobalObj;
var apPlatform;
var lFailCount;


var iTestID = 53669;

var g_OnDBCS = false;
var g_lang = "";

function GetLang()
{
	g_lang = apGlobalObj.apGetLangExt(apGlobalObj.LangHost());
	if(g_lang == "JP" || g_lang == "KO" || g_lang == "CHS" || g_lang == "CHT")
		g_OnDBCS = true;
}
 
function ucase07 () {

    apInitTest("ucase07 ");
    GetLang();

    var Expected, Result;
    var Temp1;
    var Temp2;

    apInitScenario("Scenario 1 - Use ucase with string constant");

    Result = "abcdefg".toUpperCase();
    Expected = "ABCDEFG";
    if ( Result != Expected ) {
	 apLogFailInfo("(ucase with constant returned " + Result + " not " + Expected + ")", "", "", "");
    }
    

	    apInitScenario("Scenario 1 - Use ucase with DBCS string constant");
    if(g_OnDBCS)
    {
	    Result = "あえいおう".toUpperCase();
	    Expected = "あえいおう";
	    if ( Result != Expected ) {
		 apLogFailInfo("(ucase with constant returned " + Result + " not " + Expected + ")", "", "", "");
	    }
    }

    apInitScenario("Scenario 2 - Use ucase with string variable");

    Temp1 = "abcdefgh";
    Result = Temp1.toUpperCase();
    Expected = "ABCDEFGH";
    if ( Result != Expected ) {
	 apLogFailInfo("(ucase with variable returned " + Result + " not " + Expected + ")", "", "", "");
    }
    

	    apInitScenario("Scenario 2 - Use ucase with DBCS string variable");
    if(g_OnDBCS)
    {
	    Temp1 = "あえいおう";
	    Result = Temp1.toUpperCase();
	    Expected = "あえいおう";
	    if ( Result != Expected ) {
		 apLogFailInfo("(ucase with variable returned " + Result + " not " + Expected + ")", "", "", "");
	    }
    }

    apInitScenario("Scenario 4 - Use ucase with string expressions");

    Temp1 = "abc";
    Temp2 = "defghijklm";
    Result = (Temp1 + Temp2).toUpperCase();
    Expected = "ABCDEFGHIJKLM";
    if ( Result != Expected ) {
	 apLogFailInfo("(ucase with string expression returned " + Result + " not " + Expected + ")", "", "", "");
    }
	

	    apInitScenario("Scenario 4 - Use ucase with DBCS string expressions");
    if(g_OnDBCS)
    {
	    Temp1 = "あえいおう";
	    Temp2 = "あえいおうあえいおう";
	    Result = (Temp1 + Temp2).toUpperCase();
	    Expected = "あえいおうあえいおうあえいおう";
	    if ( Result != Expected ) {
		 apLogFailInfo("(ucase with string expression returned " + Result + " not " + Expected + ")", "", "", "");
	    }
    }

    apEndTest();
}


ucase07();


if(lFailCount >= 0) System.Environment.ExitCode = lFailCount;
else System.Environment.ExitCode = 1;

function apInitTest(stTestName) {
    lFailCount = 0;

    apGlobalObj = new Object();
    apGlobalObj.apGetPlatform = function Funca() { return "Rotor" }
    apGlobalObj.LangHost = function Funcb() { return 1033;}
    apGlobalObj.apGetLangExt = function Funcc(num) { return "EN"; }

    apPlatform = apGlobalObj.apGetPlatform();
    var sVer = "1.0";  //navigator.appVersion.toUpperCase().charAt(navigator.appVersion.toUpperCase().indexOf("MSIE")+5);
    apGlobalObj.apGetHost = function Funcp() { return "Rotor " + sVer; }
    print ("apInitTest: " + stTestName);
}

function apInitScenario(stScenarioName) {print( "\tapInitScenario: " + stScenarioName);}

function apLogFailInfo(stMessage, stExpected, stActual, stBugNum) {
    lFailCount = lFailCount + 1;
    print ("***** FAILED:");
    print ("\t\t" + stMessage);
    print ("\t\tExpected: " + stExpected);
    print ("\t\tActual: " + stActual);
}

function apGetLocale(){ return 1033; }
function apWriteDebug(s) { print("dbg ---> " + s) }
function apEndTest() {}
