#include "testApp.h"

vector<ofPoint> vertices;
vector<ofColor> colors;

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	shader.setGeometryInputType(GL_TRIANGLES);
	shader.setGeometryOutputType(GL_TRIANGLES);
	shader.setGeometryOutputCount(4);
	//Load shader
		//shader.load( "shaderVert.c", "shaderFrag.c" );
	shader.load( "shaderVert.c", "shaderFrag.c", "shaderGeom.c" );
	
	sphere.setRadius(75);
	sphere.setResolution(2);
	
	triangles = sphere.getMesh().getUniqueFaces();
	testMesh.setFromTriangles(triangles);
	
	
	shatterNow = false;
	shatterTime = false;
}

//--------------------------------------------------------------
float time0 = 0;
float phase = 0;
float distortAmount = 0;

void testApp::update(){
  //Compute dt
  float time = ofGetElapsedTimef();
  float dt = ofClamp( time - time0, 0, 0.1 );
  time0 = time;

  float speed = ofMap( mouseY, 0, ofGetHeight(), 0, 5 );
  phase += speed * dt;
  distortAmount = ofMap( mouseX, 0, ofGetWidth(), 0, 0.5);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofEnableDepthTest();				//Enable z-buffering

	//Set a gradient background from white to gray
	//for adding an illusion of visual depth to the scene
	ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );

		//sphere.draw();
	
	
	ofPushMatrix();	//Store the coordinate system

		//Move the coordinate center to screen's center
		ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
		//Calculate the rotation angle
		float time = ofGetElapsedTimef();	//Get time in seconds
		float angle = time * 10;			//Compute angle. We rotate at speed 10 degrees per second
		ofRotate( angle, 0, 1, 0 );			//Rotate the coordinate system along y-axe

		//Enable the shader
		shader.begin();		
		shader.setUniform1f( "phase", phase );
		shader.setUniform1f( "distortAmount", distortAmount );
	
		if (shatterNow){
			shatterTime +=0.75;
			if (shatterTime<150) {
				
			} else {
				shatterNow = false;
			}
		} else {
			shatterTime = 0;
		}
	
		shader.setUniform1f( "shatterTime", shatterTime );
		
		
		shader.setGeometryOutputCount(1024);
			ofDisableBlendMode();
			testMesh.drawFaces();
		//glLineWidth(2);
			ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
			testMesh.drawWireframe();
	
			
		shader.end();	//Disable the shader

	ofPopMatrix();	//Restore the coordinate system
	
	
	
	ofSetColor(255, 255, 255);
	ofDrawBitmapString("shatterTime : "+ofToString(ofGetFrameRate()) ,
					   20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
		//shatterNow = false;
	shatterNow = true;
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}