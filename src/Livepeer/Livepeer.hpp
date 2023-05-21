#include <curl/curl.h>
#include <string>
#include <fstream>

#include "utils.hpp"
#include "json.hpp"

#define REQUEST_UPLOAD "https://livepeer.com/api/asset/request-upload"
#define RETRIEVE_ASSET "https://livepeer.com/api/asset/"
#define EXPORT_ASSET "https://livepeer.com/api/asset/" // ENDS WITH $ASSET_ID/export

class Livepeer {
public:
	Livepeer() {
		char* tempAPIKey = std::getenv("LIVEPEER_API_KEY");

		if (!tempAPIKey) {
			throw std::runtime_error("Missing LIVEPEER_API_KEY");
		}

		this->APIKEY = tempAPIKey;

		curl_global_init(CURL_GLOBAL_DEFAULT);
	}

	~Livepeer() {
		curl_global_cleanup();
	}

	std::string exportAssetToIPFS(const std::string& assetID);
	void uploadContent(const std::string& filePath, const std::string& assetURL);
	nlohmann::json retrieveAsset(const std::string& assetID);
	nlohmann::json getLivepeerUrl(const std::string& videoName);

private:
	std::string APIKEY;
};

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* s);
size_t readCallback(void* ptr, std::streamsize size, size_t nmemb, void* stream);