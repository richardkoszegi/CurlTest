// CurlTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "curl/curl.h"
#include <iostream>
#include <string>

class OneDriveHandler {
private:
	char* clientId = "";
public:
	void LogIn() {
		CURL* logincurl = curl_easy_init();
		if (logincurl) {
			CURLcode res;

			char* scope = "onedrive.readwrite";
			char loginaddress[2000];
			strcpy_s(loginaddress, "https://login.live.com/oauth20_authorize.srf?client_id=");
			strcat_s(loginaddress, clientId);
			strcat_s(loginaddress,"&scope=" );
			strcat_s(loginaddress, scope);
			strcat_s(loginaddress, "&response_type=token&redirect_uri=https://login.live.com/oauth20_desktop.srf");

			curl_easy_setopt(logincurl, CURLOPT_URL, loginaddress);
			curl_easy_setopt(logincurl, CURLOPT_HTTPGET, 1L);

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
		std::cout << "[LOG] Logout begin\n";
		CURL* logoutcurl = curl_easy_init();
		if (logoutcurl) {
			CURLcode res;

			char logoutaddress[2000];
			strcpy_s(logoutaddress, "https://login.live.com/oauth20_logout.srf?client_id=");
			strcat_s(logoutaddress, clientId);
			strcat_s(logoutaddress,"&redirect_uri=https://login.live.com/oauth20_desktop.srf" );

			curl_easy_setopt(logoutcurl, CURLOPT_URL, logoutaddress);
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

int main()
{
	curl_global_init(CURL_GLOBAL_ALL);

	OneDriveHandler* odh = new OneDriveHandler();
	odh->LogIn();

	odh->LogOut();

	std::cin.get();

	curl_global_cleanup();
    return 0;
}

