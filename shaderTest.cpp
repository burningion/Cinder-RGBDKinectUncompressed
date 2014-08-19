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
    std::vector<std::string> texturez;
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
    fs::path p("/Users/kirkkaiser/Desktop/DepthKit_006_OSX/video_shoot/TAKE_08_16_14_46_31/depth");
    outty = fs::path("/Users/kirkkaiser/Desktop/DepthKit_006_OSX/video_shoot/TAKE_08_16_14_46_31/render/");
    for( fs::directory_iterator it( p ); it != fs::directory_iterator(); ++it ) {
        if( ! is_directory( *it ) ) {
            if (it->path().filename() == ".DS_Store") continue;
            console() << "   " << it->path().filename() << " size(bytes): " <<                                   fs::file_size( *it ) << std::endl;
            texturez.push_back(it->path().filename().string());
        }
    }
	
	mAngle = 0.0f;
    outpuddded = 0;
}

void ImageFileTestApp::keyDown( KeyEvent event )
{
	if( event.getCode() == app::KeyEvent::KEY_f ) {
		setFullScreen( ! isFullScreen() );
	}
}

void ImageFileTestApp::update()
{

}

void ImageFileTestApp::draw()
{
	gl::clear();

	mTexture->enableAndBind();
	mShader->bind();
	mShader->uniform( "tex0", 0 );
	gl::drawSolidRect( getWindowBounds() );

	mTexture->unbind();
    if (outpuddded == 0)
        {
            std::string yep = outty.string() + std::string("outty.png");
            writeImage(yep, copyWindowSurface());
            outpuddded = 1;
        }
}


CINDER_APP_BASIC( ImageFileTestApp, RendererGl )