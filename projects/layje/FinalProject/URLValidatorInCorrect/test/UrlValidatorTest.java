

import junit.framework.TestCase;
import java.util.Random;


//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testYourFirstPartition()
   {
	 System.out.println("TESTING ALLOW ALL SCHEMES\n");
	 
	 runTests(true);
	  
	  
   }
   
   public void testYourSecondPartition(){
	   System.out.println("TESTING OPTIONS ENABLED\n"); 
	   
	   runTests(false);

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   	ResultPair[] scheme = {new ResultPair("http://", true),
							   new ResultPair("https://", true),
							   new ResultPair("ftp://", true),
							   new ResultPair("mailto://", true),
							   new ResultPair("data://", true),
							   new ResultPair("irc://", true),
							   new ResultPair("http:/", false),
							   new ResultPair("http:", false),
							   new ResultPair("http/", false),
							   new ResultPair("http:\\", false),
							   new ResultPair("http\\", false),
							   new ResultPair("://", false)};
		
		ResultPair[] authority = {new ResultPair("0.0.0.0", true),
								  new ResultPair("255.com", true),
								  new ResultPair("255.255.255.255", true),
								  new ResultPair("256.256.256.256", false),
								  new ResultPair("go.au", true),										
								  new ResultPair("go.auto", true),
								  new ResultPair("1.2.3", false),
								  new ResultPair("1.2.3.4.", false),
								  new ResultPair(".1.2.3.4", false),
								  new ResultPair("1.2.3.4.5", false),
								  new ResultPair("go.a", false),
								  new ResultPair("go.a1b", false),
								  new ResultPair("go.1ab", false),
								  new ResultPair("abc.", false),
								  new ResultPair(".abc", false),
								  new ResultPair("abc", false),
								  new ResultPair("", false)};
	
		ResultPair[] port = {new ResultPair(":80", true),
							 new ResultPair(":0", true),
							 new ResultPair("", true),
							 new ResultPair(":65535", true),
							 new ResultPair(":65536", false),
							 new ResultPair(":655aa", false),
							 new ResultPair(":-1", false),
							 new ResultPair(":999999999999999999", false)};
		
		ResultPair[] path = {new ResultPair("/testing", true),
							 new ResultPair("/testing/", true),
							 new ResultPair("/$1234", true),
							 new ResultPair("/test1234", true),
							 new ResultPair("/$1234/file", true),
							 new ResultPair("/testing/file", true),
							 new ResultPair("/test1234/file", true),
							 new ResultPair("", true),
							 // new ResultPair("//", true),
							 new ResultPair("/..", false),
							 new ResultPair("/../", false),
							 new ResultPair("/../file", false),
							 new ResultPair("/..//file", false),
							 new ResultPair("/testing//file", false)};

		ResultPair[] query = {new ResultPair("?key1=value1", true),
							  new ResultPair("?key1=value1&key2=value2", true),									
							  new ResultPair("", true),
							  new ResultPair("//", false),
							  new ResultPair("//key1=value1", false),
							  new ResultPair("//key1=value1&key2=value2", false)};		

		boolean[] testSchemeValid = {true, true, true, true, true, true, false, false, false, false, false, false};
		boolean[] testAuthorityValid = {true, true, true, false, true, true, false, false, false, false, false, false, false, false, false, false, false};
		boolean[] testPortValid = {true, true, true, true, false, false, false, false};
		boolean[] testPathValid = {true, true, true, true, true, true, true, true, false, false, false, false, false};
		boolean[] testQueryValid = {true, true, true, false, false, false};
		
		boolean newResult = true;
		int bugTracker = 0;

		for(int index = 0; index < scheme.length; index++)
			if(testSchemeValid[index] != scheme[index].valid)
				newResult = false;
		for(int index = 0; index < authority.length; index++)
			if(testAuthorityValid[index] != authority[index].valid)
				newResult = false;	
		for(int index = 0; index < port.length; index++)
			if(testPortValid[index] != port[index].valid)
				newResult = false;	
		for(int index = 0; index < path.length; index++)
			if(testPathValid[index] != path[index].valid)
				newResult = false;
		for(int index = 0; index < query.length; index++)
			if(testQueryValid[index] != query[index].valid)
				newResult = false;

		if(newResult == false)
		{
			System.out.println("---------------- Bug Tracked ----------------");
			System.out.println("ResultPair valid storage error.");
			System.out.println("-------------------- End --------------------");
			bugTracker++;
		}
		else
			System.out.println("SUCCESS: ResultPair valid storage success.");

		boolean oneFalse = false;
	
		UrlValidator urlValidator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);	
		
		for (int oneIndex = 0; oneIndex < scheme.length; oneIndex++) 
		{
			ResultPair[] schemePart = (ResultPair[]) scheme;	

			for (int twoIndex = 0; twoIndex < authority.length; twoIndex++) 
			{
				ResultPair[] authorityPart = (ResultPair[]) authority;
				
				for (int threeIndex = 0; threeIndex < port.length; threeIndex++) 
				{
					ResultPair[] portPart = (ResultPair[]) port;

					for (int fourIndex = 0; fourIndex < path.length; fourIndex++) 
					{
						ResultPair[] pathPart = (ResultPair[]) path;

						for (int fiveIndex = 0; fiveIndex < query.length; fiveIndex++)
						{
							ResultPair[] queryPart = (ResultPair[]) query;
							
							boolean notOneFalseFlag = false;
							boolean expected = true;
							
							int totalFalse = 0;
							if(schemePart[oneIndex].valid == false)
								totalFalse++;
							if(authorityPart[twoIndex].valid == false)
								totalFalse++;
							if(portPart[threeIndex].valid == false)
								totalFalse++;
							if(pathPart[fourIndex].valid == false)
								totalFalse++;
							if(queryPart[fiveIndex].valid == false)
								totalFalse++;
							
							if(totalFalse > 0)
								expected = false;
							
							if(oneFalse == true)
								if(totalFalse != 1)
									notOneFalseFlag = true;

							StringBuilder compositeString = new StringBuilder();
							
							compositeString.append(schemePart[oneIndex].item);
							compositeString.append(authorityPart[twoIndex].item);
							compositeString.append(portPart[threeIndex].item);
							compositeString.append(pathPart[fourIndex].item);
							compositeString.append(queryPart[fiveIndex].item);
														
							String url = compositeString.toString();
							
							try 
							{
								boolean result = urlValidator.isValid(url);	
								
								if(expected != result && notOneFalseFlag == false)
								{
									System.out.println("---------------- Bug Tracked ----------------");
									System.out.println("Result: " + result);
									System.out.println("Expected: " + expected);
									System.out.println("URL: " + url);
									System.out.println("valid: " + schemePart[oneIndex].valid + "	scheme: " + schemePart[oneIndex].item);
									System.out.println("valid: " + authorityPart[twoIndex].valid + "	host: " + authorityPart[twoIndex].item);
									System.out.println("valid: " + portPart[threeIndex].valid + "	port: " + portPart[threeIndex].item);
									System.out.println("valid: " + pathPart[fourIndex].valid + "	path: " + pathPart[fourIndex].item);
									System.out.println("valid: " + queryPart[fiveIndex].valid + "	query: " + queryPart[fiveIndex].item);
									System.out.println("-------------------- End --------------------");

									bugTracker++;
									notOneFalseFlag = false;
								}								
							} 
							catch (Error errorCause) 
							{

								System.out.println("---------------- Bug Tracked ----------------");
								System.out.println("Error: " + errorCause);
								System.out.println("URL: " + url);
								System.out.println("valid: " + schemePart[oneIndex].valid + "	scheme: " + schemePart[oneIndex].item);
								System.out.println("valid: " + authorityPart[twoIndex].valid + "	host: " + authorityPart[twoIndex].item);
								System.out.println("valid: " + portPart[threeIndex].valid + "	port: " + portPart[threeIndex].item);
								System.out.println("valid: " + pathPart[fourIndex].valid + "	path: " + pathPart[fourIndex].item);
								System.out.println("valid: " + queryPart[fiveIndex].valid + "	query: " + queryPart[fiveIndex].item);
								System.out.println("-------------------- End --------------------");

								bugTracker++;
								notOneFalseFlag = false;
							}
						}
					}
				}
			}	
		}

		if(bugTracker == 0)
			System.out.println("SUCCESS: No Bugs Found\nTotal Bugs Tracked: " + bugTracker);	
		else
			System.out.println("ERRORS FOUND:\nTotal Bugs Tracked: " + bugTracker);

	}

   

   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   public void printTestFail(String item, boolean expected, boolean actual) {
	   	 System.out.println("TEST FAILURE");
		 System.out.println("URL: " + item);
		 System.out.println("EXPECTED: " + expected);
		 System.out.println("ACTUAL: " + actual + "\n");
   }
   
   public void runTests(boolean optionsIn) {
	   
	   	 long options = UrlValidator.ALLOW_ALL_SCHEMES;
	   	 
	   	 if (optionsIn == false) {
	   		options =
	   	            UrlValidator.ALLOW_2_SLASHES
	   	                + UrlValidator.ALLOW_ALL_SCHEMES
	   	                + UrlValidator.NO_FRAGMENTS;
	   	 }
	   	 
	   	 int numTests = 50000;
		 
		 UrlValidator urlVal = new UrlValidator(null, null, options);
		 assertTrue(urlVal.isValid("http://www.google.com"));
	     assertTrue(urlVal.isValid("http://www.google.com/"));
		 
	     //AUTHORITY ONLY RANDOMIZED
	     System.out.println("AUTHORITY ONLY RANDOMIZED\n");
	    
	     int failures = 0;
	     
	     for (int i = 0; i < numTests; i++) {
	    	 ResultPair testCase = (ResultPair) genAuthTest();
	    	 
	    	 boolean result = urlVal.isValid(testCase.item);
	    	 
	    	 if (result != testCase.valid) {
	    		 failures++;
	    		 printTestFail(testCase.item, testCase.valid, result);
	    	 }
	     }
	     
	     System.out.println("TOTAL FAILURES: " + Integer.toString(failures));
	     System.out.println("");
	     
	     //PORT ONLY RANDOMIZED
	     System.out.println("PORT ONLY RANDOMIZED\n");
	     
	     failures = 0;
	     
	     for (int i = 0; i < numTests; i++) {
	    	 ResultPair testCase = (ResultPair) genPortTest();
	    	 
	    	 boolean result = urlVal.isValid(testCase.item);
	    	 
	    	 if (result != testCase.valid) {
	    		 failures++;
	    		 printTestFail(testCase.item, testCase.valid, result);
	    	 }
	     }
	     
	     System.out.println("TOTAL FAILURES: " + Integer.toString(failures));
	     System.out.println("");
	     
	   //PATH ONLY RANDOMIZED
	     System.out.println("PATH ONLY RANDOMIZED\n");
	     
	     failures = 0;
	     
	     for (int i = 0; i < numTests; i++) {
	    	
	    	 ResultPair testCase = (ResultPair) genPathTest(optionsIn);
	    	 
	    	 boolean result = urlVal.isValid(testCase.item);
	    	 
	    	 if (result != testCase.valid) {
	    		 failures++;
	    		 printTestFail(testCase.item, testCase.valid, result);
	    	 }
	     }
	     
	     System.out.println("TOTAL FAILURES: " + Integer.toString(failures));
	     System.out.println("");
	     
	     
	     //ALL RANDOMIZED
	     System.out.println("ALL PORTIONS RANDOMIZED\n");
	     failures = 0;
	     
	     for (int i = 0; i < numTests; i++) {
	    	 ResultPair testCase = (ResultPair) genAllTest(optionsIn);
	    	 
	    	 boolean result = urlVal.isValid(testCase.item);
	    	 
	    	 
	    	 if (result != testCase.valid) {
	    		 failures++;
	    		 printTestFail(testCase.item, testCase.valid, result);
	    	 }
	    	 
	     }
	     
	     
	     
	     System.out.println("TOTAL FAILURES: " + Integer.toString(failures) + "\n");
   }
   
   
   
   /*
    * The Internet standards (Requests for Comments) for protocols mandate that 
    * component hostname labels may contain only the ASCII letters 'a' through 'z' 
    * (in a case-insensitive manner), the digits '0' through '9', and the minus sign 
    * ('-'). The original specification of hostnames in RFC 952, mandated that labels 
    * could not start with a digit or with a minus sign, and must not end with a minus 
    * sign. However, a subsequent specification (RFC 1123) permitted hostname labels to 
    * start with digits. No other symbols, punctuation characters, or white space are 
    * permitted.
    * 
    * https://en.wikipedia.org/wiki/Hostname
    */
   
   
   
   public Object genRandomAuth() {
	   
	   StringBuilder authBuffer = new StringBuilder();
	   Random rand = new Random();
	   
	   //random valid 
	   if (rand.nextInt(2) == 1) {
		   
		   String[] starts = {"www.", ""};
		   String[] ends = {".com", ".org", ".co", ".edu", ".au", ".uk"};
		   String alphaFirstLast = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		   String alphaMid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-.";
		   boolean lastDot = false;
		   
		   //random valid string
		   if (rand.nextInt(2) == 1) {
			   authBuffer.append(starts[rand.nextInt(starts.length)]);
			   
			   int midLen = rand.nextInt(50) + 1;
			   
			   for (int i = 0; i < midLen; i++) {
				   
				   if (lastDot == true || i == 0 || i == midLen - 1) {
					   char choice = alphaFirstLast.charAt(rand.nextInt(alphaFirstLast.length()));
					   
					   authBuffer.append(choice);
					   
					   if (lastDot == true) {
						   lastDot = false;
					   }
				   }
				   else {
					   char choice = alphaMid.charAt(rand.nextInt(alphaMid.length()));
					   
					   authBuffer.append(choice);
					   
					   if (choice == '.') {
						   lastDot = true;
						   
						   while (authBuffer.charAt(authBuffer.length() - 2) == '-' || 
								  authBuffer.charAt(authBuffer.length() - 2) == '.' ) {
							   authBuffer.setCharAt(authBuffer.length() - 2, alphaMid.charAt(rand.nextInt(alphaMid.length())));
						   }
					   }
				   }
				   
			   }
			   
			   authBuffer.append(ends[rand.nextInt(ends.length)]);
			   
		   }
		   
		   //random valid nums
		   else {
			   
			   for (int i = 0; i < 4; i++) {
				   
				   int val = rand.nextInt(254) + 1;
				   
				   Integer.toString(val);
				   
				   authBuffer.append(val);
				   
				   if (i < 3) {
					   authBuffer.append(".");
				   }
			   }  
		   }
		   
		   String retStr = authBuffer.toString();
		   
		   return new ResultPair(retStr, true);
		   
	   }
	   //random invalid
	   else {
		   
		   //random invalid string
		   if (rand.nextInt(2) == 1) {
			   
			   String alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_@#$^*:;~";
			   
			   int len = rand.nextInt(300) + 1;
		   
			   for (int i = 0; i < len; i++) {
			   
				   char choice = alpha.charAt(rand.nextInt(alpha.length()));
			   
				   authBuffer.append(choice);
			   }
		   }
		   //random invalid nums 
		   else {
			   
			   if (rand.nextInt(2) == 1) {
				   //invalid format
				   int dotCount = 0;
				   String alpha = ".0123456789";
				   
				   while (dotCount < 4) {
					   char choice = alpha.charAt(rand.nextInt(alpha.length()));
					   
					   authBuffer.append(choice);
					   
					   if (choice == '.') {
						   dotCount++;
					   }
				   }
			   }
			   else {
				   for (int i = 0; i < 4; i++) {
					   
					   int val = rand.nextInt(1000) + 255;
					   
					   Integer.toString(val);
					   
					   authBuffer.append(val);
					   
					   if (i < 3) {
						   authBuffer.append(".");
					   }
				   }  
			   }
		   }
		   
		   String retStr = authBuffer.toString();
		   
		   return new ResultPair(retStr, false);
	   }
	    
   }
   
   public Object genRandomPort() {
	   
	   Random rand = new Random();
	   
	   String alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	   
	   //1/2 create a port
	   if (rand.nextInt(2) == 1) {
		   
		   StringBuilder portBuffer = new StringBuilder();
		   boolean expected = true;
		   
		   portBuffer.append(":");
		   
		   //random value for port
		   int portVal = rand.nextInt(999999) + 1;
		   
		   int randChoice = rand.nextInt(6);
		   
		   //1/6 make port negative vale
		   if (randChoice == 1) {
			   portVal = -portVal;
		   }
	
		   //1/6 put a char in the port before number
		   if (randChoice == 2) {
			   portBuffer.append(alpha.charAt(rand.nextInt(alpha.length())));
			   expected = false;
		   }
		   
		   //set false for port out of valid range
		   if (randChoice != 2 && (portVal > 65535 || portVal < 0)) {
			   expected = false;
		   }
		   
		   Integer.toString(portVal);
		   
		   portBuffer.append(portVal);
		   
		   //1/6 put a char in the port after number
		   if (randChoice == 3) {
			   portBuffer.append(alpha.charAt(rand.nextInt(alpha.length())));
			   expected = false;
		   }
		   
		   
		   String retStr = portBuffer.toString();
		   
		   return new ResultPair(retStr, expected);
		   
	   }
	   //no port specified
	   else {
		   return new ResultPair("", true);
	   }    
   }
   
   public Object genRandomPath(boolean no2) {
	   Random rand = new Random();
	   
	   //1/4 create a path
	   if (rand.nextInt(2) == 1) {
		   
		   
		   StringBuilder pathBuffer = new StringBuilder();
		   boolean expected = true;
		   
		   //valid path
		   if (rand.nextInt(2) == 1) {
			   
			   String alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-?.";
			   
			   int pathSeg = rand.nextInt(10) + 1;
			   
			   for (int i = 0; i < pathSeg; i++) {
				   
				   pathBuffer.append("/");
				   
				   int segLen = rand.nextInt(20) + 1;
				   
				   for (int j = 0; j < segLen; j++) {
					   char choice = alpha.charAt(rand.nextInt(alpha.length()));
					   
					   while (choice == '.' && i == 0) {
						   choice = alpha.charAt(rand.nextInt(alpha.length()));
					   }
					   
					   pathBuffer.append(choice);
				   }
			   }
		   }
		   //invalid path
		   else {
			   
			   String alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-?";
			   
			   
			   //int doubSlash = rand.nextInt(2);
			   int pathSeg = rand.nextInt(10) + 1;
			   
			   expected = false;
			   
			   for (int i = 0; i < pathSeg; i++) {
				   
				   if (no2 == true && rand.nextInt(2) == 1) {
					   
					   pathBuffer.append("//");
				   }
				   
				   else {
					   
					   pathBuffer.append("/../");
					   
				   }
				   
				   int segLen = rand.nextInt(20) + 1;
				   
				   for (int j = 0; j < segLen; j++) {
					   char choice = alpha.charAt(rand.nextInt(alpha.length()));
					   
					   pathBuffer.append(choice);
				   }	   
			   }
			   
		   }
		   
		   String retStr = pathBuffer.toString();
		   
		   return new ResultPair(retStr, expected);
		   
	   }
	   //no path specified
	   else {
		   return new ResultPair("", true);
	   }
   } 
   
   public Object genAllTest(boolean optionsIn) {
	   Random rand = new Random();
	   StringBuilder testBuffer = new StringBuilder();
	   boolean expected = true;
	   
	   //scheme
	   int schIdx = rand.nextInt(testUrlScheme.length);
	   testBuffer.append(testUrlScheme[schIdx].item);
	   expected &= testUrlScheme[schIdx].valid;
	     
	   //authority
	   ResultPair randAuth = (ResultPair) genRandomAuth();
	   testBuffer.append(randAuth.item);
	   expected &= randAuth.valid; 
	   
	   //port
	   ResultPair randPort = (ResultPair) genRandomPort();
	   testBuffer.append(randPort.item);
	   expected &= randPort.valid;
	   
	   //path
	   ResultPair randPath = (ResultPair) genRandomPath(optionsIn);
	   testBuffer.append(randPath.item);
	   expected &= randPath.valid;
	   
	   //query
	   int queryIdx = rand.nextInt(testUrlQuery.length);
	   testBuffer.append(testUrlQuery[queryIdx].item);
	   expected &= testUrlQuery[queryIdx].valid; 
	   
	   String retStr = testBuffer.toString();
	   
	   return new ResultPair(retStr, expected);
   }
   
   
   public Object genAuthTest() {
	  
	   StringBuilder testBuffer = new StringBuilder();
	   boolean expected = true;
	   
	   //scheme
	   testBuffer.append("http://");
	     
	   //authority
	   ResultPair randAuth = (ResultPair) genRandomAuth();
	   testBuffer.append(randAuth.item);
	   expected &= randAuth.valid; 
	   
	   
	   String retStr = testBuffer.toString();
	   
	   return new ResultPair(retStr, expected);
   }
  
   
   public Object genPortTest() {
	 
	   StringBuilder testBuffer = new StringBuilder();
	   boolean expected = true;
	   
	   //scheme and authority
	   testBuffer.append("http://www.google.com");
	     
	   //port
	   ResultPair randPort = (ResultPair) genRandomPort();
	   testBuffer.append(randPort.item);
	   expected &= randPort.valid;
	   
	   String retStr = testBuffer.toString();
	   
	   return new ResultPair(retStr, expected);
   }
   
   public Object genPathTest(boolean optionsIn) {
	  
	   StringBuilder testBuffer = new StringBuilder();
	   boolean expected = true;
	   
	   //scheme and authority - no port
	   testBuffer.append("http://www.google.com");
	   
	   //path 
	   ResultPair randPath = (ResultPair) genRandomPath(optionsIn);
	   testBuffer.append(randPath.item);
	   expected &= randPath.valid; 
	   
	   String retStr = testBuffer.toString();
	   
	   return new ResultPair(retStr, expected);
   }
   
   
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false)};

   
   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
           new ResultPair("?action=edit&mode=up", true),
           new ResultPair("", true)};
}