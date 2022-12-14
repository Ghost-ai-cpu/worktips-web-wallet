// Copyright (c) 2014-2015, MyWorktips.com
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

thinwalletApp.config(function ($routeProvider, $locationProvider) {
    "use strict";
    //$locationProvider.html5Mode(false);
    $routeProvider
        .when('/', {
            templateUrl: 'partials/home.html',
            controller: 'VersionCtrl',
            title: 'Welcome',
            redirectToAccount: true
        })
        .when('/overview', {
            templateUrl: 'partials/account-overview.html',
            controller: 'AccountOverviewCtrl',
            title: 'Overview',
            authenticated: true
        })
        .when('/transactions', {
            templateUrl: 'partials/account-transactions.html',
            controller: 'TransactionsCtrl',
            title: 'Transactions',
            authenticated: true
        })
        .when('/send', {
            templateUrl: 'partials/send-coins.html',
            controller: 'SendCoinsCtrl',
            title: 'Send coins',
            authenticated: true
        })
        .when('/receive', {
            templateUrl: 'partials/receive-coins.html',
            controller: 'ReceiveCoinsCtrl',
            title: 'Receive coins',
            authenticated: true
        })
        .when('/create-your-account', {
            templateUrl: 'partials/create-your-account.html',
            controller: 'GenerateWalletCtrl',
            title: 'Create your account',
            redirectToAccount: true
        })
        .when('/support', {
            templateUrl: 'partials/support.html',
            title: 'Support'
        })
        .when('/privacy-policy',  {
            templateUrl: 'partials/privacy-policy.html',
            title: 'Privacy policy'
        })
        .when('/terms', {
            templateUrl: 'partials/terms.html',
            title: 'Terms of use'
        })
        .otherwise({
            redirectTo: '/'
        });
});
