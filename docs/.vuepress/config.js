const { fs, path } = require('@vuepress/shared-utils')

module.exports = ctx => ({
  dest: './dist',
  locales: {
    '/': {
      lang: 'zh-CN',
      title: '笃行',
      description: '笃行致远，不负芳华'
    },
    '/en/': {
      lang: 'English',
      title: 'Practice',
      description: 'The back-end architects self practice'
    }
  },
  head: [
    ['link', { rel: 'icon', href: `/logo.png` }],
    ['link', { rel: 'manifest', href: '/manifest.json' }],
    ['meta', { name: 'theme-color', content: '#3eaf7c' }],
    ['meta', { name: 'apple-mobile-web-app-capable', content: 'yes' }],
    ['meta', { name: 'apple-mobile-web-app-status-bar-style', content: 'black' }],
    ['link', { rel: 'apple-touch-icon', href: `/icons/apple-touch-icon-152x152.png` }],
    ['link', { rel: 'mask-icon', href: '/icons/safari-pinned-tab.svg', color: '#3eaf7c' }],
    ['meta', { name: 'msapplication-TileImage', content: '/icons/msapplication-icon-144x144.png' }],
    ['meta', { name: 'msapplication-TileColor', content: '#000000' }]
  ],
  themeConfig: {
    repo: 'm9rco/practice',
    docsRepo: 'm9-lab/m9-lab.github.io',
    docsBranch: 'master',
    editLinks: true,
    docsDir: 'docs',
    algolia: ctx.isProd ? ({
      apiKey: '17103d809d3df489f3e1de21aaa02b48',
      indexName: 'practice'
    }) : null,
    smoothScroll: true,
    locales: {
      '/': {
        label: '简体中文',
        selectText: '选择语言',
        ariaLabel: '选择语言',
        editLinkText: '在 GitHub 上编辑此页',
        lastUpdated: '上次更新',
        nav: require('./nav/zh'),
        sidebar: {
          '/zh/guide/': getGuideSidebar('指南', '深入'),
          '/zh/db/': getDbSidebar('关系型数据库','键-值数据库','列数据库','文档型数据库','图数据库'),
          '/zh/os/': getOsSidebar('操作系统','计算机原理'),
          '/zh/program/':getProgramSidebar('解释型语言','编译型语言')
        }
      },
      '/en': {
        label: 'English',
        selectText: 'Languages',
        ariaLabel: 'Select language',
        editLinkText: 'Edit this page on GitHub',
        lastUpdated: 'Last Updated',
        nav: require('./nav/en'),
        sidebar: {
        }
      }
    }
  },
  plugins: [
    ['@vuepress/back-to-top', true],
    ['@vuepress/pwa', {
      serviceWorker: true,
      updatePopup: true
    }],
    ['@vuepress/medium-zoom', true],
    ['@vuepress/google-analytics', {
      ga: 'UA-158536766-1'
    }],
    ['container', {
      type: 'vue',
      before: '<pre class="vue-container"><code>',
      after: '</code></pre>'
    }],
    ['container', {
      type: 'upgrade',
      before: info => `<UpgradePath title="${info}">`,
      after: '</UpgradePath>'
    }],
    ['flowchart']
  ],
  extraWatchFiles: [
    '.vuepress/nav/en.js',
    '.vuepress/nav/zh.js'
  ]
})

function getOsSidebar(argumentA,argumentB) {
  return [
    {
      title: argumentA,
      collapsable: false,
      children: [
        'io',
        'cpu',
        'thread',
        'coroutines',
        'process',
      ]
    },
    {
      title: argumentB,
      collapsable: false,
      children: [
        'linux',
      ]
    },
  ];
}

function getProgramSidebar(argumentA,argumentB) {
  return [
    {
      title: argumentA,
      collapsable: false,
      children: [
        'php',
        'python',
        'javascript',
      ]
    },
    {
      title: argumentB,
      collapsable: false,
      children: [
        'golang',
        'c'
      ]
    },
  ];
}

function getDbSidebar (groupA, groupB, groupC, groupD,groupE) {
  return [
    {
      title: groupA,
      collapsable: false,
      children: [
        'mysql',
        'postgreSQL',
      ]
    },
    {
      title: groupB,
      collapsable: false,
      children: [
        'redis',
      ]
    },
    {
      title: groupC,
      collapsable: false,
      children: [
        'hbase',
        'clickhouse',
      ]
    },
    {
      title: groupD,
      collapsable: false,
      children: [
        'mongodb',
      ]
    },
    {
      title: groupE,
      collapsable: false,
      children: [
        'neo4j',
      ]
    }
  ]
}

function getGuideSidebar (groupA, groupB) {
  return [
    {
      title: groupA,
      collapsable: false,
      children: [
        '',
      ]
    }
  ]
}

// const officalPlugins = fs
//   .readdirSync(path.resolve(__dirname, '../plugin/official'))
//   .map(filename => 'official/' + filename.slice(0, -3))
//   .sort()

function getPluginSidebar (pluginTitle, pluginIntro, officialPluginTitle) {
  return [
    {
      title: pluginTitle,
      collapsable: false,
      children: [
        ['', pluginIntro],
        'using-a-plugin',
        'writing-a-plugin',
        'life-cycle',
        'option-api',
        'context-api'
      ]
    },
    {
      title: officialPluginTitle,
      collapsable: false,
      children: []
    }
  ]
}

function getThemeSidebar (groupA, introductionA) {
  return [
    {
      title: groupA,
      collapsable: false,
      sidebarDepth: 2,
      children: [
        ['', introductionA],
        'using-a-theme',
        'writing-a-theme',
        'option-api',
        'default-theme-config',
        'blog-theme',
        'inheritance'
      ]
    }
  ]
}
