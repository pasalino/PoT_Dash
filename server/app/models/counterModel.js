'use strict';


const fs = require('fs');
const {promisify} = require('util');
const path = require('path');
const fsReadProm = promisify(fs.readFile);
const fsReaddirProm = promisify(fs.readdir);
const fsAppendFile = promisify(fs.appendFile);
const fsUnlink = promisify(fs.unlink);
const {Promise} = require('bluebird');


const Visitor = function (meeting) {
    this.data = new Date();
    this.meeting = meeting;
};

module.exports = {


    increment: async (meeting) => {
        const visitor = new Visitor(meeting);
        const baseData = global.config.server.dataFolder;
        await fsAppendFile(`${baseData}/${meeting}.txt`, JSON.stringify(visitor) + '\n');
    },


    clear: async (meeting) => {
        const baseData = global.config.server.dataFolder;
        await fsUnlink(`${baseData}/${meeting}.txt`);
    },

    getTotalVisitorsInMeeting: async (meeting) => {
        const baseData = global.config.server.dataFolder;
        const data = await fsReadProm(`${baseData}/${meeting}.txt`);
        let res = data.toString().split('\n').length;
        res--;
        if (res < 0) res = 0;
        return res;
    },

    getMeetingList: async () => {
        const baseData = global.config.server.dataFolder;
        let files = await fsReaddirProm(baseData);
        files = await Promise.filter(files, file => {
            return ".txt" === path.extname(file);
        });

        let result = [];
        for (const f of files) {
            const name = f.replace('.txt', '');
            const count = await module.exports.getTotalVisitorsInMeeting(name);
            result.push({name, count})
        }
        return result;
    },
};

