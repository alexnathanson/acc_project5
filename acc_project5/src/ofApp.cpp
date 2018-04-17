#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);

	//OF knows to load both your vert and frag shaders together
	mShader.load("shaders/sphere/shader");

	ofLoadImage(mTex, "images/mercator.png");

	ofBackground(0);
	//could do a distance map thing to avoid a 2nd shader?
	bShader.load("shaders/background/shader");

	ofEnableDepthTest();

	mSphere.set(150.0f, 4);

	//uncomment to use texture
	mTex.setTextureWrap(GL_NEAREST, GL_NEAREST);
	mTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	mSphere.mapTexCoordsFromTexture(mTex);

	ofDisableArbTex();

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofSetColor(255, 0, 0);

	ofDrawBitmapString("a-b-c changes sphere. 1 2 3 changes background", 10, 20);

	// translate plane into center screen.
	float tx = ofGetWidth() / 2;
	float ty = ofGetHeight() / 2;

	bShader.begin();

	bShader.setUniform1f("u_time", ofGetElapsedTimef());
	bShader.setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
	bShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	bShader.end();

	ofPushMatrix();
	ofTranslate(tx, ty, 250.0);

	mShader.begin();
	mShader.setUniform1f("u_time", ofGetElapsedTimef());
	mShader.setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
	mShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());

	float rotation = fmod(ofGetFrameNum() * 0.01, 360.0);
	//ofLogNotice("rotation", ofToString(rotation));
	//ofRotateY(rotation);

	//mSphere.draw(OF_MESH_WIREFRAME);
	mSphere.draw();
	
	//uncomment to use texture
	mTex.bind();
	mShader.end();

	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	switch (key){
	case '1':
		mShader.load("shaders/sphere/shader");
		break;
	case '2':
		mShader.load("shaders/sphere2/shader");
		break;
	case '3':
		mShader.load("shaders/sphere2/shader");
		break;
	case 'a':
		bShader.load("shaders/background/shader");
		break;
	case 'b':
		bShader.load("shaders/background2/shader");
		break;
	case 'c':
		bShader.load("shaders/background2/shader");
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
