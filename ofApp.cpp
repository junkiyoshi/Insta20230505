#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(1);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum());
	ofRotateX(cos(ofGetFrameNum() * 0.05) * 15);

	float len = 300;
	float span = len * 1.5;
	ofColor color;

	for (int k = 0; k < 4; k++) {

		ofRotateY(90);

		for (int i = 0; i < 20; i++) {

			vector<glm::vec3> vertices;
			for (int param = 0; param < 100; param++) {

				float deg = param * 3.6 - 135;
				float noise_value = ofNoise(k, cos(deg * DEG_TO_RAD) * 0.5, sin(deg * DEG_TO_RAD) * 0.5, i * 0.013 + ofGetFrameNum() * 0.02);

				auto location = glm::vec3(this->make_point(len, param), 150);

				if (noise_value > 0.5) {

					vertices.push_back(location);
				}
				else {

					vertices.push_back(glm::normalize(location) * 100);
				}
			}

			color.setHsb(ofMap(i, 0, 15, 0, 255), 255, 200);
			ofSetColor(color);

			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}

	//ofFill();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
