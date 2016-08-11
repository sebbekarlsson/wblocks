# Website Compiler
> Generate websites using css/html/js modules and json.

## About
> WebsiteCompiler is a lightweight program written in C++, it is designed to
> make it easier to create small website projects.
> Create simple or advanced websites using json-configurations.

## Install
> To install websitecompiler, run:

        sudo ./install.sh

## Usage
> * To create your first project (we will call it blog), simply run:

        websitecompiler boil blog

> This will generate a boilerplate for you, called "blog".
>
> Inside if this folder you should see the following files and folders:
>
> * modules/
> * fonts/
> * site.json
> * index.json
>
> This is the basic structure of a project.
> Let us go through each of these files/folders:

#### modules/
> Inside of the modules folder is where you will be storing your html/css/js
> modules.
>
> This could for example be ... (images sliders, galleries, banners,
> navigation bars...etc)
>
> If you have used the "boil" command, you should already see a module inside
> of this folder; called: "hero".
> This module is simply a big banner with a centered text.
>
> Modules are later used in your *.json files.

#### fonts/
> Inside of the fonts folder is where you will store your font-config files.
>
> Font-config files contains tree different values:
>
> * family - (The name of the font)
> * fallback-family (The name of the fallback-family incase of problems with
> the main one)
> * link - (The link/url/location to the font)
>
> If you used to "boil" command, you should already see a font-config
> inside of the
> fonts folder, this config is called "lato.json".

#### site.json
> This is the main config for your website.
>
> The site.json is where most of the settings of your website is set.
> The main ingridients of this file is:
>
> * Title - (The title of your website)
> * Font - (The path to which font-config to use)
> * Pages - (The path to each page that you are using)
>
> If you used the "boil" command, you should already have some data in your
> site.json file.
> There should be one page already defined; called: "index.json"

#### index.json
> This is a page, in this case: the main page.
>
> If you used the "boil" command, this page will already have some content/data.
> It should already have a section with a child-module that is using the
> included "hero" module.

## Compiling the website/project
> To compile/transpile/export your project, simply run:

        websitecompiler compile blog

> "blog" could be anything that you named your project directory.
>
> This command will create another folder which will have the name of the
> <b>title</b> value inside of your site.json
>
> To view the generated/compiled/transpiled website, simply open the index.html
> file using any browser you want.
