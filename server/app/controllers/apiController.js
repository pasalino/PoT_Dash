'use strict';
const cors = require('cors');
const bodyParser = require('body-parser');
const model = require('../models/counterModel');


module.exports = function (app) {
    const api_base = global.config.server.apiBasePath + '/counter';

    app.route(api_base + '/:meeting').patch(cors(), bodyParser.json(), async (req, res) => {
        const meeting = req.params.meeting;

        console.log(`Increment meeting: ${meeting}`);
        await model.increment(meeting);

        const response = {status: 200, success: 'Increment Successfully'};
        res.status(response.status);
        res.json(response);
    });

    app.route(api_base + '/:meeting').delete(cors(), bodyParser.json(), async (req, res) => {
        const meeting = req.params.meeting;

        await model.clear(meeting);

        const response = {status: 202, meeting, success: 'Meeting reset'};
        res.status(response.status);
        res.json(response);
    });
};
