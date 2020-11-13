const path = require('path')
const VueLoaderPlugin = require('vue-loader/lib/plugin')

module.exports = {
    mode: 'development',
    entry: {
        mainvue: './src/vueapp.js',
        style: './assets/scss/style.scss',
    },
    output: {
        path: path.resolve(__dirname, 'bundles/'),
        filename: '[name].js',
    },
    module: {
        rules: [
            {
                test: /\.vue$/,
                loader: 'vue-loader'
            },
            {
                test: /\.js$/,
                loader: 'babel-loader'
            },
            {
                test: /\.css$/,
                use: [
                    'vue-style-loader',
                    'css-loader',
                    'sass-loader'
                ]
            },
            {
                test: /\.scss$/,
                use: [
                    {
                        loader: 'file-loader',
                        options: {
                            outputPath: 'css/',
                            name: '[name].css'
                        }
                    },
                    {
                        loader: 'sass-loader',
                        options: {
                            sourceMap: true,
                            sassOptions: {
                                outputStyle: 'compressed',
                            }
                        }
                    }
                ]
            },
            {
                test: /\.(jpe?g|png|gif|woff|woff2|eot|ttf|svg)(\?[a-z0-9=.]+)?$/,
                use: [
                    {
                        loader: 'url-loader',
                        options: {
                            publicPath: path.resolve(__dirname, 'assets/img/'),
                            esModule: false,
                        },
                    }
                ]
            }
        ]
    },
    plugins: [
        new VueLoaderPlugin()
    ]
}