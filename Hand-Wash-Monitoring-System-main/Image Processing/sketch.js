// Add some header info
// For TM template code

// Video
let video;
let label = "waiting...";
let classifier;

var config = {
    apiKey: "AIzaSyDTRRAr_d0tUhqO73ibpKPV1M7VG2Te5H8",
    authDomain: "livonian-9de64.firebaseapp.com",
    databaseURL: "https://livonian-9de64.firebaseio.com",
    projectId: "livonian-9de64",
    storageBucket: "livonian-9de64.appspot.com",
    messagingSenderId: "49100749025",
    appId: "1:49100749025:web:f17d404a32a88f506f5fa0"
};
firebase.initializeApp(config);

//create firebase database reference
var dbRef = firebase.database();
var contactsRef = dbRef.ref('steps');



// STEP 1: Load the model!
function preload(){
  classifier = ml5.imageClassifier('model.json');
}

function setup() {
  createCanvas(640, 520);
  // Create the video
    let constraints = {
    video: {
      mandatory: {
        
        id: 2
      },
      
    },
    
  };
  video = createCapture(VIDEO);
  video.hide();

  // STEP 2: Start classifying
  classifyVideo();
}

// STEP 2 classify!
function classifyVideo() {
  classifier.classify(video, gotResults);
}

function draw() {
  background(0);
  
  // Draw the video
  image(video, 0, 0);

  // STEP 4: Draw the label
    textSize(32);
  textAlign(CENTER, CENTER);
  fill(255);
  text(label, width / 2, height - 16);
}



// STEP 3: Get the classification!
function gotResults(error, results) {
  // Something went wrong!
  if (error) {
    console.error(error);
    return;
  }
  label = results[0].label;
  classifyVideo();
  if (results[0].label == 'none')
{
contactsRef.push({
        step1: '1',
        step2: '0'
});

}
}

