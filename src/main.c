#include <curl/curl.h>

int main() {
	
	CURL* handle = curl_easy_init();
	curl_easy_setopt(handle, CURLOPT_URL, "https://www.mediafire.com/file/ntw63tjx4fy96rw/otaku-adventure-v1.3.0.apk");
	curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(handle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36");
	
	
	printf("%i\n", (int) curl_easy_impersonate(handle, "chrome110", 0));
	const CURLcode code = curl_easy_perform(handle);
	
}