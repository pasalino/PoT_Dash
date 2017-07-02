'use strict';
const model = require('../models/counterModel');

module.exports = function (app) {
    app.route('/').all(async (req, res) => {
        const list = await model.getMeetingList();
        const context = {list};
        res.render(`list`, context);
    });
};
