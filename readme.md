# Readme

tcm is a small helper oduel to get a component-based workflow also in your theme-layer.

It scans two folders of your them and register every found component as a theming function in your theme.

## Installation

Install the module as usual. Add the following to your hook_theme-implementation:

```
function mytheme_theme($existing, $type, $theme, $path) {

  $theme_declaration = tcm_register_theme_functions($existing, $type, $theme, $path);

  // Your existing theme-declarations:
  $theme_declaration['mytheme'] = array()

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

The component.json-file should include at least a name-property, and if you want to use it from the backend-site, a backend-property:

```
{
  "name": "slideshow item",
  "backend": {
    "template": "slideshow-item.tpl.haml",
    "arguments": {
      "image": {
        "src": "http://fillmurray.com/200/300"
      }
    }
  }
}
```

  * ``name`` the name of the component
  * ``description`` the description of the component
  * ``backend``
    * ``template`` should containt the filename of your template-file
    * ``arguments`` is a json-object describing the default arguments for this component
  * ``styles`` / ``scripts``: the module has preliminary support for embedding styles + JS defined in a component
    It's usually better to use duo.js/ grunt to package your frontend-files together.
    If you want, that drupal adds styles and or scripts when using a component, then set the variable ``tcm_attach_assets`` to TRUE.


## Usage

If you want to include a component in one of your template-files, just use

```
  <?php print component('component-name', array( your arguments))); ?>
```


##See also

  * http://duojs.org
