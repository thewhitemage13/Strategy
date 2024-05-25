#include <iostream>
using namespace std;

class Reader {
public:
    virtual ~Reader(){}
    virtual void Parse(string& url) = 0;
};

class ResourceReader {
private:
    Reader* reader;
public:
    ResourceReader(Reader* r) : reader(r) {};
    ~ResourceReader() { delete reader; }
    
    void SetStrategy(Reader* r) {
        if (reader != nullptr)delete reader;
        reader = r;
    }
    void Read(string& url) {
        reader->Parse(url);
    }
};

class NewsSiteReader : public Reader {
public:
    void Parse(string& url) override {
        cout << "news site parsing: " << url << "\n";
    }
};

class SocialNetworkReader : public Reader {
public:
    void Parse(string& url) override {
        cout << "parsing news feed from a social network: " << url << "\n";
    }
};

class TelegramChannelReader : public Reader {
public:
    void Parse(string& url) override {
        cout << "Telegram messenger channel parsing: " << url << "\n";
    }
};

int main() {
    ResourceReader* res = new ResourceReader(new NewsSiteReader());
    string url = "https://news.com";
    res->Read(url);

    url = "https://facebook.com";
    res->SetStrategy(new SocialNetworkReader());
    res->Read(url);

    url = "@news_channel_telegram";
    res->SetStrategy(new TelegramChannelReader());
    res->Read(url);
}