// CurlTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "curl/curl.h"
#include <iostream>
#include <string>

class OneDriveHandler {
private:
	std::string clientId = "EwB4Aq1DBAAUGCCXc8wU/zFu9QnLdZXy+YnElFkAAXAwLjh7gB45zz6o5M4ocELU5RYeqEwMTOIWfntTBVnJft6s45CTBJzi6l3TPorrtm8dIK+ClySddsWWqk2UsCmRsT9RITtGlfkiQS+4yXMKSGiVOUjQGNMnQ8t0caZsux/Y+0nh/UFotkRsIFj0A08OFoPj7PngWlvo3OmHYTImnj+O9+oWINPXlQtht9cRe8uyYLzv6tmim9V4PGKIVugypkkQsogq1yUVcZ9cKPw70kXV0CSJFtsVR6A+qhz8MGpJ/nz/wi4FtomfJG6uVyFHsEcZZxuWJX7GgMj/9iEyPOg8ztqLRz+NPt/AgJvbcjgC8ikLIoMRm0+MHsjKgSkDZgAACFpQlLGLrTzQSAGrSVor0q2kSzlT21ZGm3mx4l9E+Wv5aLqRnnQfwBEn8TRlEuxljGwgPt16IPyYQUlRRde0HeSXFyv35BpnTX2+Ciu6VhGNZ+8SqmBniS0XKYqNKV9CG/5ln7mXgPNb3IIdw9BwDcs3H6mm/PHRDqiPOnlc4KDYhc/n5rDVOMHCMQy3hGwpBg598Npl7p2m6WjrMRy+RJ7EeuHIsoxfdeffRok5aFjbhO+Cia1bkQnNtJDIsrSQW4oqQJISdNXwNmW17Gv4Cv0QI6VztIrKP5QVF3mQmG3BuhKGaFwAESFtg0SIdHdzA0TGpsqovC4VENIgp00qajFzTGzsv+9jQiRu1ae+IXSvnEtFakDZjs2p1DZU/pDUTQ21Fr1/KJIQvEOqf7Kp/ZQWwVTwM+RpiXzopVIg2knta/PqoTBcoWyram+22jCE8rf2aAE=";
public:
	void LogIn() {
		CURL* logincurl = curl_easy_init();
		if (logincurl) {
			CURLcode res;
			std::string scope = "onedrive.readwrite";
			std::string loginaddress = "https://login.live.com/oauth20_authorize.srf?client_id="+clientId+"&scope="+scope+"&response_type=token&redirect_uri= https://login.live.com/oauth20_desktop.srf";
			std::cout << loginaddress+"\n";
			curl_easy_setopt(logincurl, CURLOPT_URL, loginaddress);
			curl_easy_setopt(logincurl, CURLOPT_HEADER, 1);
			//curl_easy_setopt(logincurl, CURLOPT_RETURNTRANSFER, 1);
			curl_easy_setopt(logincurl, CURLOPT_HTTPGET, 1);
			curl_easy_setopt(logincurl, CURLOPT_DNS_USE_GLOBAL_CACHE, false);
			curl_easy_setopt(logincurl, CURLOPT_DNS_CACHE_TIMEOUT, 2);

			res = curl_easy_perform(logincurl);
			curl_easy_cleanup(logincurl);


			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
			else {
				std::cout << res;
				std::cout << "\n[LOG] Login Done\n";
			}
		}
	}

	void LogOut() {
		CURL* logoutcurl = curl_easy_init();
		if (logoutcurl) {
			CURLcode res;
			std::string loginaddress = "https://login.live.com/oauth20_logout.srf?client_id=" + clientId + "&redirect_uri= https://login.live.com/oauth20_desktop.srf";
			curl_easy_setopt(logoutcurl, CURLOPT_URL, loginaddress);
			res = curl_easy_perform(logoutcurl);
			curl_easy_cleanup(logoutcurl);

			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));
			else {
				std::cout << res;
				std::cout << "\n[LOG] Logout Done\n";
			}
		}
	}

	void UploadFiel() {}
};

void test() {
	CURL* curl = curl_easy_init();
	if (curl) {
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
		else {
			std::cout << res;
			std::cout << "\n[LOG] Logout Done\n";
		}
	}
}


int main()
{
	curl_global_init(CURL_GLOBAL_ALL);

	OneDriveHandler* odh = new OneDriveHandler();
	odh->LogIn();

	odh->LogOut();
	//test();

	std::cin.get();

	curl_global_cleanup();
    return 0;
}

