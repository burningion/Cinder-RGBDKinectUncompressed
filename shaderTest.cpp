#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/Filesystem.h"

#include "Resources.h"

using namespace ci;
using namespace ci::app;

class ImageFileTestApp : public AppBasic {
 public: 	
	void setup();
	void keyDown( KeyEvent event );
	
	void update();
	void draw();
	
	gl::TextureRef	mTexture;	
	gl::GlslProgRef	mShader;
	float			mAngle;
    int outpuddded;
    fs::path outty;
    fs::path inny;
    std::vector<std::string> texturez;
    std::vector<int> indexez;
    std::vector<int> indexez24p;
    std::vector<std::string> reddy2render;
    int counter;
};


void ImageFileTestApp::setup()
{
	try {
		mTexture = gl::Texture::create( loadImage( loadResource( RES_IMAGE_JPG ) ) );
	}
	catch( ... ) {
		std::cout << "unable to load the texture file!" << std::endl;
	}
	
	try {
		mShader = gl::GlslProg::create( loadResource( RES_PASSTHRU_VERT ), loadResource( RES_BLUR_FRAG ) );
	}
	catch( gl::GlslProgCompileExc &exc ) {
		std::cout << "Shader compile error: " << std::endl;
		std::cout << exc.what();
	}
	catch( ... ) {
		std::cout << "Unable to load shader" << std::endl;
	}
    
    std::cout << "Iterating over directory: /Users/kirkkaiser/Desktop/DepthKit_006_OSX/video_shoot/TAKE_08_16_14_46_31/depth" << std::endl;
    
    inny = fs::path("/Users/kirkkaiser/Desktop/DepthKit_006_OSX/video_shoot/TAKE_08_16_14_46_31/depth/");
    outty = fs::path("/Users/kirkkaiser/Desktop/DepthKit_006_OSX/video_shoot/TAKE_08_16_14_46_31/render/");
    
    for( fs::directory_iterator it( inny ); it != fs::directory_iterator(); ++it ) {
        if( ! is_directory( *it ) ) {
            if (it->path().filename() == ".DS_Store") continue;
            console() << "   " << it->path().filename() << " size(bytes): " <<                                   fs::file_size( *it ) << std::endl;
            texturez.push_back(it->path().filename().string());
        }
    }
    
    for (int i = 0; i < texturez.size(); i++) {
        // make an array of the integer values of milliseconds into an array
        // so we can get back down to 24p homie
        std::string filename = texturez[i];
        int start = filename.find("millis_") + 7;

        std::string daMillis = filename.substr(start, 10);
        int daNum = std::stoi(daMillis);
        console() << daNum << std::endl;
        indexez.push_back(daNum);
    }
    
    float idealInterval = 41.6666; // SO CLOSE TO 42! interval in millis between frames for target framerate 1000 / 24
    int lastFrameUsed = 0;
    int frame = -1;
    
    // algo below to sort to as close to 24 p as possible
	while (lastFrameUsed < indexez.size()) {
        frame++;
        int millis = frame * idealInterval;
        while (millis > indexez[lastFrameUsed]) {
            lastFrameUsed++;
            if (lastFrameUsed >= indexez.size()) break;
        }
        indexez24p.push_back(lastFrameUsed);
    }

    for (int i =0; i < indexez24p.size(); i++) {
        reddy2render.push_back(texturez[indexez24p[i]]); // populate our array with strings of proper filenames
    }
    
    /* verify that we've got the right stuff
    for (int i = 0; i < reddy2render.size(); i++) {
        console() << reddy2render[i] << std::endl;
    } */
    
	mAngle = 0.0f;
    outpuddded = 0;
    counter = 1;
}

void ImageFileTestApp::keyDown( KeyEvent event )
{
	if( event.getCode() == app::KeyEvent::KEY_f ) {
		setFullScreen( ! isFullScreen() );
	}
}

void ImageFileTestApp::update()
{
    if (outpuddded < reddy2render.size()) {
        mTexture = gl::Texture::create( loadImage( inny.string() + reddy2render[counter - 1] ) );
        counter++;
    }
}

void ImageFileTestApp::draw()
{
	gl::clear();

	mTexture->enableAndBind();
	mShader->bind();
	mShader->uniform( "tex0", 0 );
	gl::drawSolidRect( getWindowBounds() );

	mTexture->unbind();
    if (outpuddded < reddy2render.size())
        {
            std::string yep = outty.string() + std::string("output") + std::to_string(counter) + std::string(".png");
            writeImage(yep, copyWindowSurface());
            outpuddded++;
        }
}


CINDER_APP_BASIC( ImageFileTestApp, RendererGl )