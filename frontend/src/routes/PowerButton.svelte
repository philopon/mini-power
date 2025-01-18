<!--
This component was generated using v0, an AI-powered coding assistant.
For more information, visit: https://v0.dev
Permanent link to this chat: https://v0.dev/chat/svelte-tailwindcss-button-s23iQXHIAMD
-->
<script lang="ts">
	import { onMount } from 'svelte';
	import Icon from '@iconify/svelte';

	export let status: boolean = false;
	export let changing: boolean = false;
	export let onClick: () => void = () => {};
	export let macAddress: string;
	export let ipAddress: string;
	export let onCopyIP: () => void;
	export let onCopyMac: () => void;
	export let onClickResetBoard: () => void;

	let showInfo: boolean = false;
	let isIPCopied: boolean = false;
	let isMACCopied: boolean = false;
	let showResetModal: boolean = false;
	let infoBoxRef: HTMLDivElement;
	let infoButtonRef: HTMLButtonElement;

	onMount(() => {
		const handleClickOutside = (event: MouseEvent) => {
			if (
				showInfo &&
				infoBoxRef &&
				!infoBoxRef.contains(event.target as Node) &&
				!infoButtonRef.contains(event.target as Node)
			) {
				showInfo = false;
			}
		};

		document.addEventListener('click', handleClickOutside);

		return () => {
			document.removeEventListener('click', handleClickOutside);
		};
	});

	function toggleInfo(event: MouseEvent): void {
		event.stopPropagation();
		showInfo = !showInfo;
	}

	function handleCopyIP(event: MouseEvent): void {
		event.stopPropagation();
		onCopyIP();
		isIPCopied = true;
		setTimeout(() => {
			isIPCopied = false;
		}, 1000);
	}

	function handleCopyMac(event: MouseEvent): void {
		event.stopPropagation();
		onCopyMac();
		isMACCopied = true;
		setTimeout(() => {
			isMACCopied = false;
		}, 1000);
	}

	function handleResetClick(): void {
		showResetModal = true;
	}

	function handleResetConfirm(): void {
		onClickResetBoard();
		showResetModal = false;
		showInfo = false;
	}

	function handleResetCancel(): void {
		showResetModal = false;
		showInfo = false;
	}
</script>

<div class="min-h-screen w-full flex flex-col bg-slate-900">
	<div class="w-full bg-slate-800 py-2 px-4 flex justify-end">
		<button
			bind:this={infoButtonRef}
			on:click={toggleInfo}
			class="text-white/80 hover:text-white focus:outline-none focus:ring-2 focus:ring-white/20 rounded-full p-1"
			aria-label="Toggle information"
		>
			<Icon icon="mdi:information" width="24" height="24" />
		</button>
	</div>

	<div class="flex-grow flex flex-col items-center justify-center gap-6">
		<button
			on:click={onClick}
			disabled={changing}
			class={`
        w-48 h-48
        rounded-full
        flex items-center justify-center
        transition-all duration-300
        transform 
        relative
        ${!changing && 'hover:scale-105'}
        focus:outline-none focus:ring-4 focus:ring-opacity-50
        ${
					status
						? 'bg-emerald-500 focus:ring-emerald-400 shadow-lg shadow-emerald-500/50'
						: 'bg-slate-700 focus:ring-slate-600'
				}
        ${changing && 'cursor-not-allowed opacity-75'}
      `}
			aria-label="Power button"
		>
			{#if changing}
				<div class="absolute inset-0 flex items-center justify-center">
					<div
						class="absolute w-full h-full rounded-full border-4 border-t-transparent border-white/30 animate-spin"
					/>
				</div>
			{/if}

			<Icon
				icon="mdi:power"
				width="48"
				height="48"
				class={`
          transition-colors duration-300
          ${changing ? 'opacity-50' : ''}
          ${status ? 'text-white' : 'text-slate-400'}
        `}
			/>
		</button>

		<div class="flex flex-col items-center gap-2 text-white/80"></div>
	</div>

	{#if showInfo}
		<div
			bind:this={infoBoxRef}
			class="absolute top-16 right-4 bg-slate-700 p-4 rounded-lg shadow-lg text-white/80"
		>
			<div class="grid grid-cols-4 gap-2 items-center">
				<span class="text-right">IP:</span>
				<div class="col-span-3 flex items-center justify-between">
					<span>{ipAddress}</span>
					<button
						on:click={(e) => handleCopyIP(e)}
						class="text-white/80 hover:text-white focus:outline-none focus:ring-2 focus:ring-white/20 rounded-full p-1 ml-2"
						aria-label="Copy IP address"
					>
						<Icon icon={isIPCopied ? 'mdi:check' : 'mdi:content-copy'} width="20" height="20" />
					</button>
				</div>
				<span class="text-right">MAC:</span>
				<div class="col-span-3 flex items-center justify-between">
					<span>{macAddress}</span>
					<button
						on:click={(e) => handleCopyMac(e)}
						class="text-white/80 hover:text-white focus:outline-none focus:ring-2 focus:ring-white/20 rounded-full p-1 ml-2"
						aria-label="Copy MAC address"
					>
						<Icon icon={isMACCopied ? 'mdi:check' : 'mdi:content-copy'} width="20" height="20" />
					</button>
				</div>
			</div>
			<div class="mt-4 pt-4 border-t border-slate-600">
				<button
					on:click={handleResetClick}
					class="w-full bg-red-600 hover:bg-red-700 text-white font-bold py-2 px-4 rounded focus:outline-none focus:shadow-outline transition duration-150 ease-in-out"
				>
					RESET
				</button>
			</div>
		</div>
	{/if}

	{#if showResetModal}
		<div class="fixed inset-0 bg-black bg-opacity-50 flex items-center justify-center z-50">
			<div class="bg-slate-800 p-6 rounded-lg shadow-xl">
				<h2 class="text-xl font-bold mb-4 text-white">Confirm Reset</h2>
				<p class="mb-6 text-white/80">Are you sure you want to reset the board?</p>
				<div class="flex justify-end space-x-4">
					<button
						on:click={handleResetCancel}
						class="px-4 py-2 bg-slate-700 text-white rounded hover:bg-slate-600 focus:outline-none focus:ring-2 focus:ring-slate-500 transition duration-150 ease-in-out"
					>
						Cancel
					</button>
					<button
						on:click={handleResetConfirm}
						class="px-4 py-2 bg-red-600 text-white rounded hover:bg-red-700 focus:outline-none focus:ring-2 focus:ring-red-500 transition duration-150 ease-in-out"
					>
						OK
					</button>
				</div>
			</div>
		</div>
	{/if}
</div>

<style>
	@keyframes spin {
		from {
			transform: rotate(0deg);
		}
		to {
			transform: rotate(360deg);
		}
	}
</style>
