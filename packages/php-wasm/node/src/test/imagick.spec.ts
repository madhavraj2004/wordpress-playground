import {
	LatestSupportedPHPVersion,
	PHP,
	getPhpIniEntries,
	setPhpIniEntries,
} from '@php-wasm/universal';
import { loadNodeRuntime } from '../lib';

describe('imagick', () => {
	let php: PHP;
	beforeEach(async () => {
		php = new PHP(await loadNodeRuntime('8.3'));
		setPhpIniEntries(php, {
			extension: 'imagick',
		});
	});

	it('generate image', async () => {
		const image = await php.run({
			code: `<?php
				header('Content-type: image/jpeg');
				$image = new Imagick('image.jpg');
				$image->thumbnailImage(100, 0);
				echo $image;`
		});

		console.log(image.text);
		expect(false).toBe(true);
	});
});
