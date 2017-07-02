module.exports = (app) => {
    const express = require('express');
    const staticAsset = require('static-asset');
    const favicon = require('serve-favicon');

    //Common assets
    app.use('/jquery', express.static('node_modules/jquery/dist/'));
    app.use('/bootstrap', express.static('node_modules/bootstrap/dist/'));

    //Favicon
    app.use(favicon(`${config.server.publicAsset}/img/favicon.png`));

    //Public assets
    app.use(staticAsset(global.config.server.publicAsset));
    app.use(express.static(global.config.server.publicAsset));
};
