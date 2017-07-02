const http = require('http');
const express = require('express');
const bodyParser = require('body-parser');

const MeetingApi = require('./controllers/apiController');

const Static = require('./middlewares/staticAsset');
const ViewsEngine = require('./middlewares/viewsEngine');
const Meeting = require('./controllers/viewController');

global.env = process.env.NODE_ENV || 'development';
global.config = require(__dirname + '/config.json')[global.env];
const port = process.env.PORT || config.server.defaultPort || 3000;


const app = express();
//Middleware
app.use(bodyParser.urlencoded({extended: true}));

//Api
MeetingApi(app);
//View Engine
ViewsEngine(app);
//Static asset
Static(app);
//Apps
Meeting(app);

app.use(function(err, req, res, next) {
    console.log('errorerrorerrorerrorerrorerrorv');
    console.error(err.stack);
    res.status(500).send('Something broke!');
});


app.set('port', port);

const server = http.createServer(app);
server.listen(port);
console.log(`listening on port ${port}`);