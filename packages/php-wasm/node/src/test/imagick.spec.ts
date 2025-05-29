import {
	LatestSupportedPHPVersion,
	PHP,
	getPhpIniEntries,
	setPhpIniEntries,
} from '@php-wasm/universal';
import { loadNodeRuntime } from '../lib';
import { readFileSync } from 'fs';

describe('imagick', () => {
	let php: PHP;
	beforeEach(async () => {
		php = new PHP(await loadNodeRuntime('8.3'));

		const data = readFileSync('./jspi/8_3_0/imagick.so');

		php.mkdir('/extensions');

		await php.writeFile('/extensions/imagick.so', new Uint8Array(data));
		await php.writeFile('/extensions/imagick.la', new Uint8Array(data));
		setPhpIniEntries(php, {
			html_errors: 'Off',
			extension: '/extensions/imagick.so',
		});
	});

	it('generate image', async () => {
		const image = await php.run({
			code: `<?php
				header('Content-type: image/jpeg');
				// $image = new Imagick('image.jpg');
				// $image->thumbnailImage(100, 0);
				// echo $image;
			`,
		});

		console.log(image.text);
		expect(false).toBe(true);
	});
});
