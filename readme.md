# Readme

tcm is a small helper module to get a component-based workflow also in your theme-layer.

It scans two folders of your theme and registers every found component as a theming function in your theme.

## Installation

Install the module as usual. Add the following to your hook_theme-implementation:

```
function mytheme_theme($existing, $type, $theme, $path) {

  $theme_declaration = tcm_register_theme_functions($existing, $type, $theme, $path);

  // Your existing theme-declarations:
  $theme_declaration['mytheme'] = array();

  return $theme_declaration;
}

```

## Folder-layout

The module traverses two subfolders of your theme:

  * components
  * components_local

Your component-folder should at least contain two files:

  * component.json
  * your_template_file.tpl.php

## The component.json-file

The component.json-file should include at least a name-property, and if you want to use it from the backend-side, a backend-property:

```
{
  "name": "slideshow item",
  "backend": {
    "template": "slideshow-item.tpl.haml",
    "options": {
      "modifier": "flexEmbed--14to9",
    },
    "fixture": {
      "image": {
        "src": "http://fillmurray.com/200/300"
      }
    },
    "variants": {
      "modifier": [
        "flexEmbed--14to9",
        "flexEmbed--16to9",
        "flexEmbed--3to2"
      ],
    }
  }
}
```

  * ``name`` the name of the component
  * ``description`` the description of the component
  * ``backend``
    * ``template`` should containt the filename of your template-file
    * ``options`` is a json-object describing the default options for this component
    * ``fixture``: is a json-object describing the fixture-data, which is used, if the component is rendered without data.
    * ``variants``: a json-object describing all possible variants to render on the component's test-page. (See below)
  * ``styles`` / ``scripts``: the module has preliminary support for embedding styles + JS defined in a component
    It's usually better to use duo.js/ grunt to package your frontend-files together.
    If you want Drupal to be able to add styles and or scripts when using a component, then set the variable ``tcm_attach_assets`` to TRUE.


## Usage

If you want to include a component in one of your template-files, just use

```
  <?php print component('component-name', array( your-data ) ); ?>
```
or, if you want to override some options of the component:
```
  <?php print component('component-name', array( your-options ), array( your-data ) ); ?>
```
The options get merged with the default-options, defined in the component.json-file.

## Fixture-functions

TCM provides some helper function to generate content. A fixture-function is prefixed with a ``#``and can have one to many arguments. Here’s an example:

```
"fixture": {
  "image": "@image(400, 300)",
  "text": "@lorem_ipsum(3)"
}
```

### Available fixture-functions:

* ``@image(width, height)`` Returns an url to a image with size `width` x `height`
* ``@lorem_ipsum(num_paragraphs, (short|medium|long))`` Renders num_paragraphs paragraphs of lorem ipsum.
* ``@lorem_ipsum_html(num_paragraphs, (short|medium|long), (decorate:1|0), (links: 1|0) )`` Render num_paragraphs as lorem ipsum, optionally with decoration and/or links.


### Implement custom fixture function.

You can implement new ficture functions or change exisiting fixture-functiony by implementing the `hook_tcm_fixture_functions_alter`-hook. Just add new fixture functions to the array.


## Variants

Variants allow you to test different combinations of data or options. Variants are rendered on the component-test page at `admin/components/<component-name>`.
Here's an example of a variant-definition:
```
"variants": {
  "headline": [
    "lorem ipsum",
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.",
    "綧 鬎鯪鯠 厏吪吙 毞泂泀 鄇鄃, 禠 蔝蓶 蛚袲褁 趡趛踠 漊 蟣襋謯 銌鞁鬿 櫱瀯"
  ],
  "layoutModifier": [
    "TestComponent-image--left",
    "TestComponent-image--center",
    "TestComponent-image--right"
  ],
  "textModifier": [
    "TestComponent-text--small",
    "TestComponent-text--medium",
    "testComponent-text--large"
  ]
}
```

This will render 3 * 3 * 3 components with all possible combinations of `headline`, `layoutModifier`and `textModifier`.

You can even set more than one data-entry per variation:

```
"variants": {
  "styles": [
    {
      "headline": "One",
      "layoutModifier": "TestComponent-image--left"
    },
    {
      "headline": "Two",
      "layoutModifier": "TestComponent-image--right"
    }
  ]
},
```

This will render 2 components on the component-test-page.

##Test-pages

You can render a list of all registered components at `admin/components`. Every component has its own test-page at `admin/components/<component-name>` where all variants (if any) are rendered. These pages are good candidates for visual regression testing and as a style-guide.


##See also

  * http://duojs.org
