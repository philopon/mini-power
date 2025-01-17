<script lang="ts">
	import * as api from '$lib/api';
	import { onMount } from 'svelte';
	import PowerButton from './PowerButton.svelte';

	let { data }: { data: api.Status } = $props();
	let changing: boolean = $state(true);

	onMount(() => {
		const source = new EventSource('/events');

		api.getStatus().then((value) => {
			data = value;
			changing = false;
		});

		function handleMessage(e: MessageEvent) {
			data = { ...data, status: JSON.parse(e.data).status };

			setTimeout(
				() => {
					changing = false;
				},
				data.status ? 15000 : 1000
			);
		}

		source.addEventListener('status', handleMessage);

		return () => source.removeEventListener('status', handleMessage);
	});

	async function onClick(): Promise<void> {
		if (changing) return;
		changing = true;

		await api.togglePower();
	}

	function onCopyIP() {
		api.copy(data.ip);
	}

	function onCopyMac() {
		api.copy(data.mac);
	}

	async function onClickResetBoard() {
		await api.resetBoard();
	}
</script>

<div class="flex items-center justify-center min-h-screen bg-gray-100">
	<PowerButton
		status={data.status}
		{changing}
		{onClick}
		macAddress={data.mac}
		ipAddress={data.ip}
		{onCopyIP}
		{onCopyMac}
		{onClickResetBoard}
	/>
</div>
