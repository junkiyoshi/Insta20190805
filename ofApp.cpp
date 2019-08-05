#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofNoFill();
	ofSetLineWidth(3);

	this->font_size = 200;
	ofTrueTypeFont font;
	font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);

	for (char c = 'A'; c <= 'Z'; c++) {

		this->chara_path.push_back(font.getCharacterAsPoints(c, true, false));
	}

	this->len = 300;
	for (int i = 0; i < 80; i++) {

		this->chara_index.push_back((int)ofRandom(this->chara_path.size()));
		this->face_index.push_back((int)ofRandom(6));
		this->location.push_back(glm::vec3(ofRandom(-this->len * 0.5, this->len * 0.5), ofRandom(-this->len * 0.5, this->len * 0.5), this->len * 0.5));
		this->progress.push_back((int)ofRandom(100));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.8);

	for (int i = 0; i < this->chara_index.size(); i++) {

		this->progress[i] = (this->progress[i] + 1) % 100;
		if (this->progress[i] == 0) {

			this->chara_index[i] = ((int)ofRandom(this->chara_path.size()));
			this->face_index[i] = ((int)ofRandom(6));
			this->location[i] = (glm::vec3(ofRandom(-this->len * 0.5, this->len * 0.5), ofRandom(-this->len * 0.5, this->len * 0.5), this->len * 0.5));

			continue;
		}

		ofPushMatrix();

		if (this->face_index[i] < 4) {

			ofRotateX(this->face_index[i] * 90);
		}
		else if(this->face_index[i] < 5) {

			ofRotateY(90);
		}
		else {

			ofRotateY(270);
		}

		auto alpha = 255;
		if (this->progress[i] > 50) {

			alpha = ofMap(this->progress[i], 50, 100, 255, 0);
		}
		ofSetColor(39, alpha);

		ofBeginShape();
		auto outline = this->chara_path[this->chara_index[i]].getOutline();

		ofBeginShape();
		for (int line_index = 0; line_index < outline.size(); line_index++) {

			if (line_index != 0) { ofNextContour(true); }

			auto vertices = outline[line_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto point = this->location[i] + (vertices[vertices_index] / 100 * this->progress[i]) + glm::vec2(this->font_size / 100 * this->progress[i] * -0.5, this->font_size / 100 * this->progress[i] * 0.5);
				if (point.y > this->len * 0.5) { point.y = this->len * 0.5; }
				if (point.y < -this->len * 0.5) { point.y = -this->len * 0.5; }
				if (point.x > this->len * 0.5) { point.x = this->len * 0.5; }
				if (point.x < -this->len * 0.5) { point.x = -this->len * 0.5; }

				ofVertex(point);
			}
		}
		ofEndShape(true);
		
		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}