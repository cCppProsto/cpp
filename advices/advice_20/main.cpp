#include <iostream>
#include <string>
#include <list>
#include <memory>

// Мейерс С. - Наиболее эффективное использование C++ - 2000 35 рекомендаций
// Правило 10 - Не допускайте утечки ресурсов в конструкторах

namespace example_1
{
  class Image
  {
    public:
      Image(std::string aName)
      {
        std::cout << "  Image::Image() start" << std::endl;
        std::cout << "  Image::Image() end" << std::endl;
      }

      ~Image()
      {
        std::cout << "  Image::~Image() start" << std::endl;
        std::cout << "  Image::~Image() end" << std::endl;
      }
  };

  class AudioClip
  {
    public:
      AudioClip(std::string aName)
      {
        std::cout << "  AudioClip::AudioClip() start" << std::endl;
        std::cout << "  AudioClip::AudioClip() end" << std::endl;
      }

      ~AudioClip()
      {
        std::cout << "  AudioClip::~AudioClip() start" << std::endl;
        std::cout << "  AudioClip::~AudioClip() end" << std::endl;
      }
  };

  class PhoneNumber
  {

  };

  class BookEntry
  {
    public:
      BookEntry(const std::string &aName
               ,const std::string &aAddress = ""
               ,const std::string &aImageFile = ""
               ,const std::string &aAudioClipFileName = "")
        :m_name{aName}
        ,m_address{aAddress}
      {
        std::cout << "BookEntry::BookEntry() start" << std::endl;

        if(aImageFile != "")
          mp_image = new Image(aImageFile);

        if(aAudioClipFileName != "")
          mp_audio_clip = new AudioClip(aAudioClipFileName);

        std::cout << "BookEntry::BookEntry() end" << std::endl;
      }

      void addPhoneNumber(const std::string &aNumber)
      {
      }

      ~BookEntry()
      {
        std::cout << "BookEntry::~BookEntry() start" << std::endl;

        delete mp_image;
        delete mp_audio_clip;

        std::cout << "BookEntry::~BookEntry() end" << std::endl;
      }

    private:
      std::string m_name;
      std::string m_address;
      std::list<PhoneNumber> m_phones;
      Image *mp_image { nullptr };
      AudioClip *mp_audio_clip { nullptr };
  };


  void test()
  {
    BookEntry book("Name", "Street", "image", "audio");
  }
}

namespace example_2
{
  class Image
  {
    public:
      Image(std::string aName)
      {
        std::cout << "  Image::Image() start" << std::endl;
        std::cout << "  Image::Image() end" << std::endl;
      }

      ~Image()
      {
        std::cout << "  Image::~Image() start" << std::endl;
        std::cout << "  Image::~Image() end" << std::endl;
      }
  };

  class AudioClip
  {
    public:
      AudioClip(std::string aName)
      {
        std::cout << "  AudioClip::AudioClip() start" << std::endl;
        std::cout << "  AudioClip::AudioClip() end" << std::endl;
      }

      ~AudioClip()
      {
        std::cout << "  AudioClip::~AudioClip() start" << std::endl;
        std::cout << "  AudioClip::~AudioClip() end" << std::endl;
      }
  };

  class PhoneNumber
  {

  };

  class BookEntry
  {
    public:
      BookEntry(const std::string &aName
               ,const std::string &aAddress = ""
               ,const std::string &aImageFile = ""
               ,const std::string &aAudioClipFileName = "")
        :m_name{aName}
        ,m_address{aAddress}
      {
        std::cout << "BookEntry::BookEntry() start" << std::endl;

        if(aImageFile != "")
          mp_image = new Image(aImageFile);

        if(aAudioClipFileName != "")
        {
          mp_audio_clip = new AudioClip(aAudioClipFileName);
          throw 1;
        }

        std::cout << "BookEntry::BookEntry() end" << std::endl;
      }

      void addPhoneNumber(const std::string &aNumber)
      {
      }

      ~BookEntry()
      {
        std::cout << "BookEntry::~BookEntry() start" << std::endl;

        delete mp_image;
        delete mp_audio_clip;

        std::cout << "BookEntry::~BookEntry() end" << std::endl;
      }

    private:
      std::string m_name;
      std::string m_address;
      std::list<PhoneNumber> m_phones;
      Image *mp_image { nullptr };
      AudioClip *mp_audio_clip { nullptr };
  };


  void test()
  {
    BookEntry book("Name", "Street", "image", "audio");
  }
}

namespace example_3
{
  class Image
  {
    public:
      Image(std::string aName)
      {
        std::cout << "  Image::Image() start" << std::endl;
        std::cout << "  Image::Image() end" << std::endl;
      }

      ~Image()
      {
        std::cout << "  Image::~Image() start" << std::endl;
        std::cout << "  Image::~Image() end" << std::endl;
      }
  };

  class AudioClip
  {
    public:
      AudioClip(std::string aName)
      {
        std::cout << "  AudioClip::AudioClip() start" << std::endl;
        std::cout << "  AudioClip::AudioClip() end" << std::endl;
      }

      ~AudioClip()
      {
        std::cout << "  AudioClip::~AudioClip() start" << std::endl;
        std::cout << "  AudioClip::~AudioClip() end" << std::endl;
      }
  };

  class PhoneNumber
  {

  };

  class BookEntry
  {
    public:
      BookEntry(const std::string &aName
               ,const std::string &aAddress = ""
               ,const std::string &aImageFile = ""
               ,const std::string &aAudioClipFileName = "")
        :m_name{aName}
        ,m_address{aAddress}
      {
        std::cout << "BookEntry::BookEntry() start" << std::endl;

        if(aImageFile != "")
          mp_image = new Image(aImageFile);

        if(aAudioClipFileName != "")
        {
          mp_audio_clip = new AudioClip(aAudioClipFileName);
          throw 1;
        }

        std::cout << "BookEntry::BookEntry() end" << std::endl;
      }

      void addPhoneNumber(const std::string &aNumber)
      {
      }

      ~BookEntry()
      {
        std::cout << "BookEntry::~BookEntry() start" << std::endl;

        delete mp_image;
        delete mp_audio_clip;

        std::cout << "BookEntry::~BookEntry() end" << std::endl;
      }

    private:
      std::string m_name;
      std::string m_address;
      std::list<PhoneNumber> m_phones;
      Image *mp_image { nullptr };
      AudioClip *mp_audio_clip { nullptr };
  };


  void test()
  {
    BookEntry *pbe { nullptr };
    try
    {
      pbe = new BookEntry("Name", "Street", "image", "audio");
    }
    catch(...)
    {
      delete pbe;
      //throw;
    }
    delete pbe;
  }
}

namespace example_4
{
  class Image
  {
    public:
      Image(std::string aName)
      {
        std::cout << "  Image::Image() start" << std::endl;
        std::cout << "  Image::Image() end" << std::endl;
      }

      ~Image()
      {
        std::cout << "  Image::~Image() start" << std::endl;
        std::cout << "  Image::~Image() end" << std::endl;
      }
  };

  class AudioClip
  {
    public:
      AudioClip(std::string aName)
      {
        std::cout << "  AudioClip::AudioClip() start" << std::endl;
        std::cout << "  AudioClip::AudioClip() end" << std::endl;
      }

      ~AudioClip()
      {
        std::cout << "  AudioClip::~AudioClip() start" << std::endl;
        std::cout << "  AudioClip::~AudioClip() end" << std::endl;
      }
  };

  class PhoneNumber
  {

  };

  class BookEntry
  {
    public:
      BookEntry(const std::string &aName
               ,const std::string &aAddress = ""
               ,const std::string &aImageFile = ""
               ,const std::string &aAudioClipFileName = "")
        :m_name{aName}
        ,m_address{aAddress}
      {
        std::cout << "BookEntry::BookEntry() start" << std::endl;

        if(aImageFile != "")
          mp_image = new Image(aImageFile);

        if(aAudioClipFileName != "")
        {
          mp_audio_clip = new AudioClip(aAudioClipFileName);
          throw 1;
        }

        std::cout << "BookEntry::BookEntry() end" << std::endl;
      }

      void addPhoneNumber(const std::string &aNumber)
      {
      }

      ~BookEntry()
      {
        std::cout << "BookEntry::~BookEntry() start" << std::endl;

        delete mp_image;
        delete mp_audio_clip;

        std::cout << "BookEntry::~BookEntry() end" << std::endl;
      }

    private:
      std::string m_name;
      std::string m_address;
      std::list<PhoneNumber> m_phones;
      Image *mp_image { nullptr };
      AudioClip *mp_audio_clip { nullptr };
  };


  void test()
  {
    std::unique_ptr<BookEntry> up;

    try
    {
      up = std::make_unique<BookEntry>("Name", "Street", "image", "audio");
    }
    catch(...)
    {
      up.reset();
    }
  }
}

namespace example_5
{
  class Image
  {
    public:
      Image(std::string aName)
      {
        std::cout << "  Image::Image() start" << std::endl;
        std::cout << "  Image::Image() end" << std::endl;
      }

      ~Image()
      {
        std::cout << "  Image::~Image() start" << std::endl;
        std::cout << "  Image::~Image() end" << std::endl;
      }
  };

  class AudioClip
  {
    public:
      AudioClip(std::string aName)
      {
        std::cout << "  AudioClip::AudioClip() start" << std::endl;
        std::cout << "  AudioClip::AudioClip() end" << std::endl;
      }

      ~AudioClip()
      {
        std::cout << "  AudioClip::~AudioClip() start" << std::endl;
        std::cout << "  AudioClip::~AudioClip() end" << std::endl;
      }
  };

  class PhoneNumber
  {

  };

  class BookEntry
  {
    public:
      BookEntry(const std::string &aName
               ,const std::string &aAddress = ""
               ,const std::string &aImageFile = ""
               ,const std::string &aAudioClipFileName = "")
        :m_name{aName}
        ,m_address{aAddress}
      {
        try
        {
          std::cout << "BookEntry::BookEntry() start" << std::endl;

          if(aImageFile != "")
            mp_image = new Image(aImageFile);

          if(aAudioClipFileName != "")
          {
            mp_audio_clip = new AudioClip(aAudioClipFileName);
            throw 1;
          }

          std::cout << "BookEntry::BookEntry() end" << std::endl;
        }
        catch(...)
        {
          cleanup();
          // throw
        }
      }

      ~BookEntry()
      {
        std::cout << "BookEntry::~BookEntry() start" << std::endl;
        cleanup();
        std::cout << "BookEntry::~BookEntry() end" << std::endl;
      }

    private:
     void cleanup()
     {
       delete mp_image;
       mp_image = nullptr;

       delete mp_audio_clip;
       mp_audio_clip = nullptr;
     }

    private:
      std::string m_name;
      std::string m_address;
      std::list<PhoneNumber> m_phones;
      Image *mp_image { nullptr };
      AudioClip *mp_audio_clip { nullptr };
  };


  void test()
  {
    BookEntry *pbe = new BookEntry("Name", "Street", "image", "audio");
    delete pbe;
  }
}

namespace example_6
{
  class Image
  {
    public:
      Image(std::string aName)
      {
        std::cout << "  Image::Image() start" << std::endl;
        std::cout << "  Image::Image() end" << std::endl;
      }

      ~Image()
      {
        std::cout << "  Image::~Image() start" << std::endl;
        std::cout << "  Image::~Image() end" << std::endl;
      }
  };

  class AudioClip
  {
    public:
      AudioClip(std::string aName)
      {
        std::cout << "  AudioClip::AudioClip() start" << std::endl;
        throw 1;
        std::cout << "  AudioClip::AudioClip() end" << std::endl;
      }

      ~AudioClip()
      {
        std::cout << "  AudioClip::~AudioClip() start" << std::endl;
        std::cout << "  AudioClip::~AudioClip() end" << std::endl;
      }
  };

  class BookEntry
  {
    public:
      BookEntry(const std::string &aName
               ,const std::string &aAddress = ""
               ,const std::string &aImageFile = ""
               ,const std::string &aAudioClipFileName = "")
      try
        :m_name{aName}
        ,m_address{aAddress}
        ,mup_image{ aImageFile != "" ? std::make_unique<Image>(aImageFile) : nullptr}
        ,mup_audio_clip{ aAudioClipFileName != "" ? std::make_unique<AudioClip>(aAudioClipFileName) : nullptr}
      {
        std::cout << "BookEntry::BookEntry() start" << std::endl;
        std::cout << "BookEntry::BookEntry() end" << std::endl;
      }
      catch(...)
      {
        //throw;
      }

      ~BookEntry()
      {
        std::cout << "BookEntry::~BookEntry() start" << std::endl;
        std::cout << "BookEntry::~BookEntry() end" << std::endl;
      }

    private:
      std::string m_name;
      std::string m_address;
      std::unique_ptr<Image> mup_image ;
      std::unique_ptr<AudioClip> mup_audio_clip ;
  };


  void test()
  {
    try
    {
      std::unique_ptr<BookEntry> pbe(new BookEntry("Name", "Street", "image", "audio"));
    }
    catch(...)
    {
      std::cout << " ddd" << std::endl;
    }
  }
}

int main()
{
  //example_1::test();
  //example_2::test();
  //example_3::test();
  //example_4::test();
  //example_5::test();
  example_6::test();

  return 0;
}
