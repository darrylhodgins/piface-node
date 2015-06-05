{
	"targets": [
    		{
			"target_name": "pfio",
			'include_dirs': [ '/usr/local/include', "<!(node -e \"require('nan')\")" ],
			"sources": [ "pfio.cc" ],
			'link_settings': {
          			'libraries': [
              				'-lpifacedigital'
				]
			}
		}
	]
}
