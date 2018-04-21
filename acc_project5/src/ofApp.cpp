#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetVerticalSync(true);

	//OF knows to load both your vert and frag shaders together
	mShader.load("shaders/sphere/shader");

	ofLoadImage(mTex,"images/eye1.png");
    eye.load("images/eye1.png");

	ofBackground(0);
	//could do a distance map thing to avoid a 2nd shader?
	bShader.load("shaders/background2/shader");

	ofEnableDepthTest();

	mSphere.set(150.0f, 4);

	//uncomment to use texture
	mTex.setTextureWrap(GL_NEAREST, GL_NEAREST);
	mTex.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    if(!davShaderOn){
	mSphere.mapTexCoordsFromTexture(eye.getTexture());
    }
	ofDisableArbTex();

}

//--------------------------------------------------------------
void ofApp::update() {
    if(davShaderOn){
        updateCounter++;
        eye.load("images/eye"+ofToString(eyeIndex)+".png");
        if(updateCounter > 5){
            eyeIndex++;
            if(eyeIndex > 6){
                eyeIndex = 1;
            }
            updateCounter = 0;
        }
            ofLogNotice("images/eye"+ofToString(eyeIndex)+".png");
        mSphere.mapTexCoordsFromTexture(eye.getTexture());
        ofEnableDepthTest();
        mSphere.set(100.0f, 4);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw() {
	
    ofSetColor(0, 0, 0);

	ofDrawBitmapString("a-b-c changes background. 1 2 3 changes sphere", 10, 20);

	// translate plane into center screen.
	float tx = ofGetWidth() / 2;
	float ty = ofGetHeight() / 2;

	bShader.begin();

	bShader.setUniform1f("u_time", ofGetElapsedTimef());
	bShader.setUniform2f("u_mouse", ofGetMouseX(), ofGetMouseY());
	bShader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    
    if(background){
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    }
    /*repulusion shader*/
    
    // assign the value for range of repulsion
     bShader.setUniform1f("range", 10);
    
    //make these stars dance!
    float mx = (cos(ofGetElapsedTimef()*10.0))+ofGetWidth()/2;
    float my = (cos(ofGetElapsedTimef()*3.0))+ofGetHeight()/2;
    
    //push star position into shader
    bShader.setUniform2f("starMovement", mx, my);
    
    float percentX = mouseX / (float)ofGetWidth();
    percentX = ofClamp(percentX, 0, 1);
    
    
    //creating colors mapped to mouse
    ofFloatColor colorOne = ofColor(25,255,251);
    ofFloatColor colorTwo = ofColor(155,25,255);
    ofFloatColor colorNew = colorOne.getLerped(colorTwo, percentX);
    
    float mouseColor[4] = {colorNew.r, colorNew.g, colorNew.b, colorNew.a};
    
    bShader.setUniform4fv("mouseColor", &mouseColor[0]);
    
    if(background3) {
    
        for(int i = 0; i<100; i++){
            for( int k = 0; k <100; k++){
                ofDrawEllipse(i*20, k*20, 2, 2);
                }
            }
    }
    


        bShader.end();
    
    
    if(!davShaderOn){
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
    
    
    
    //Davs Shader start
    
    if(davShaderOn){
        mShader.begin();
        mShader.setUniformTexture("tex0", eye.getTexture(), 2);
        eye.getTexture().bind();
        ofPushMatrix();
        float rotation = 360 - fmod(ofGetFrameNum(), 360.0);
        float tx = ofGetWidth() / 2;
        float ty = ofGetHeight() / 2;
        ofTranslate(tx, ty);
        ofRotate(rotation, 0, 1.0, 0.0);
        mSphere.drawWireframe();
        mSphere.draw(ofPolyRenderMode::OF_MESH_FILL);
        ofPopMatrix();
        mShader.end();
    
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	switch (key){
	case '1':
		mShader.load("shaders/sphere/shader");
            davShaderOn = false;
		break;
	case '2':
		mShader.load("shaders/sphere2/shader");
            davShaderOn = false;
		break;
	case '3':
		mShader.load("shaders/sphere3/shader");
            davShaderOn = true;
		break;
	case 'a':
		bShader.load("shaders/background2/shader");
             background = true;
		break;
	case 'b':
		bShader.load("shaders/background3/shader");
             background = true;
            
		break;
	case 'c':
		bShader.load("shaders/background2/shader");
             background3 = true;
             background = false;
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
